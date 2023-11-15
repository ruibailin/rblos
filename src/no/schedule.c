/*
 * kernel.c
 *
 *  Created on: Apr 13, 2021
 *      Author: steve
 */


#include "0ctr.h"
/*================================================================*/
#include "./kernel/r_msg.h"
#include "./kernel/r_tcb.h"
#include "./kernel/r_pat.h"
#include "./kernel/r_pcb.h"
extern	int	sys_pno;
/*================================================================*/
/*----------------------------------------*/
#include <time.h>
#include <sys/time.h>
static	long	get_us(void);
static	long	get_us()
{
	short int	us;
    struct timeval    tv;
    struct timezone	  tz;
	gettimeofday(&tv, &tz);
	us=(int)(tv.tv_usec);
	return(us);
}

/*----------------------------------------*/
#include <unistd.h>
static	void	sleep_us(int us);
static	void	sleep_us(int us)
{
	usleep(us);
}
/*----------------------------------------*/
static	int	sch_one_msg(void);
static	int	sch_one_msg()
{
	int	node;

	node=get_msg_arrived();
	if(node==0)	return 0;

	sys_pno=get_msg_dest(node);
	set_pcb_event(sys_pno,node);	//save event ptr
	run_pcb_node(sys_pno);
	free_msg_arrived(node);
	return 1;
}

/*----------------------------------------*/
static	int	sch_one_tcb_msg(void);
static	int	sch_one_tcb_msg()
{
	int	next,node;
	int dd,ee;
	next=get_tcb_arrived();

	if(next == 0)	return 0;
	dd=get_tcb_pno(next);
	ee=get_tcb_tno(next);
	node=get_idle_msg(0,ee,0);
	set_busy_msg(node,dd,(void *)0L);
	free_tcb_arrived(next);
	return 1;

}

/*----------------------------------------*/
#include <stdio.h>
static	void sch_all_msg(void);
static	void sch_all_msg()
{
	long last_us,this_us;
	int ret1,ret2;
	int consume_time;

	consume_time = 0;
	for(;;)
	{
		last_us = get_us();
		ret1 = sch_one_msg();
		ret2 = sch_one_tcb_msg();
		this_us = get_us();

		consume_time += (this_us-last_us);
		if(MIN_SCH_CYCLE < consume_time)
		{
			printf("two busy!\n");
			break;
		}
		if(ret1)
			continue;
		if(ret2)
			continue;
		break;			//no mesg
	}
}

/*================================================================*/
extern	int ini_test_proc(void);
int consume_time;
int cpu_rate;
static void report_cpu_rate();
static void report_cpu_rate()
{
	float rate;
	rate =  consume_time/(10*1000);
	cpu_rate = rate*100;
	consume_time = 0;
	printf("cpu rate %d\n",cpu_rate);
}
int no_main(int argc, char **argv)
{
	long	last_us,this_us;
	int len;
	int count_1s;

	ini_tcb_list();
	ini_msg_list();
	ini_pcb_list();

	ini_test_proc();
	run_pcb_list();

	consume_time = 0;
	count_1s = 100;
	last_us = get_us();
	for(;;)
	{
		sch_all_msg();
		this_us = get_us();
		len = (this_us-last_us);
		consume_time += len;
		if(len < 10*1000)		//debug
			sleep_us(10*1000-len);

		run_tcb_list();
		count_1s --;
		last_us = get_us();
		if(count_1s !=0)
			continue;
		count_1s = 100;
		report_cpu_rate();
	}
	return 0;
}

/*================================================================*/
/* end of kernel.c */
