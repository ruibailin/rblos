
/*windows consol GUI*/

#include "r_msg.h"
#include "r_tcb.h"
#include "r_pat.h"
#include "r_pcb.h"
#include "r_sema.h"
#include <time.h>
#include <sys/time.h>

extern	int	sys_pno;
/*================================================================*/
static	short int	last_ms;
static	short int	this_ms;
/*----------------------------------------*/
static	short int	get_ms(void);
static	short int	get_ms()
{
	short int	ms;
    struct timeval    tv;
    struct timezone	  tz;
	gettimeofday(&tv, &tz);
	ms=(short int)(tv.tv_usec/1000);
	return(ms);
}
/*----------------------------------------*/
static	int	check_10ms(void);
static	int	check_10ms()
{	
	short int	delta_ms;
	this_ms = get_ms();
	if(this_ms < last_ms)
	{
		delta_ms=1000+this_ms-last_ms;
		if(delta_ms<10)		return(0);
		last_ms += 10;
		if(last_ms<1000)	return(1);
		last_ms -= 1000;
		return(1);
	}
	else
	{
		delta_ms=this_ms-last_ms;
		if(delta_ms<10)		return(0);
		last_ms += 10;
		return(1);
	}
}
/*----------------------------------------*/
static	void	sch_msg_loop(void);
static	void	sch_msg_loop()
{
	int	node;

	node=get_msg_arrived();
	if(node==0)	return;

	sys_pno=get_msg_dest(node);
	set_pcb_event(sys_pno,node);	//save event ptr
	run_pcb_node(sys_pno);
	free_msg_arrived(node);
	wait_sema();
}
	

/*----------------------------------------*/
static	short	int	c_10ms=0;
static	void	sch_10ms_loop(void);
static	void	sch_10ms_loop()
{
	int	next;
	if(check_10ms() == 0) return;
	
	c_10ms++;
	
	run_tcb_list();
	next=get_pcb_next(1);
	for(;;)
	{
		if(next == 1)	break;
		sys_pno=next;
		run_pcb_node(sys_pno);
		next=get_pcb_next(sys_pno);
	}
}
/*----------------------------------------*/
static	short	int	c_100ms=0;
static	void	sch_100ms_loop(void);
static	void	sch_100ms_loop()
{
	int	next;
	if(c_10ms <10) return;
	
	c_10ms=0;
	c_100ms++;
	next=get_pcb_next(2);
	for(;;)
	{
		if(next == 2)	break;
		sys_pno=next;
		run_pcb_node(sys_pno);
		next=get_pcb_next(sys_pno);
	}
}	
/*----------------------------------------*/
static	long	c_1s=0;
static	void	sch_1s_loop(void);
static	void	sch_1s_loop()
{
	int	next;
	if(c_100ms <10) return;
	
	c_100ms=0;
	c_1s++;
	next=get_pcb_next(3);
	for(;;)
	{
		if(next == 3)	break;
		sys_pno=next;
		run_pcb_node(sys_pno);
		next=get_pcb_next(sys_pno);
	}
}	
/*----------------------------------------*/
static	void	sch_tcb_loop(void);
static	void	sch_tcb_loop()
{
	int	next,node;
	int dd,ee;
	next=get_tcb_arrived();
	for(;;)
	{
		if(next == 0)	break;
		dd=get_tcb_pno(next);
		ee=get_tcb_tno(next);
		node=get_idle_msg(0,ee,0);
		set_busy_msg(node,dd,(void *)0L);
		post_sema();

		free_tcb_arrived(next);
		next=get_tcb_arrived();
	}
}	
/*--------------------------------------*/
static	void	run_pro_first(void);
static	void	run_pro_first()
{
	int next;
	next=get_pcb_next(0);
	for(;;)
	{
		if(next == 0)	break;
		sys_pno=next;
		run_pcb_node(sys_pno);
		next=get_pcb_next(sys_pno);
	}
}

/*================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
/*--------------------------------------*/
static void *pthread_entry(void *arg)
{
    int pthread_arg = *(int *)arg;

    while (1) {
    	post_sema();
        usleep(10000);
    }

    return NULL;
}

/*--------------------------------------*/
extern	ini_test_proc(void);

int	main()
{
	pthread_t tid;
	int ret;

	ini_tcb_list();
	ini_msg_list();
	
	ini_test_proc();
	
	ini_pcb_list();
	init_sema();

	last_ms=get_ms();

	run_pro_first();
	ret = pthread_create(&tid, NULL, pthread_entry, &sys_pno);
    if (ret)   exit(ret);
	for(;;)
	{
		wait_sema();
		sch_msg_loop();
		sch_10ms_loop();
		sch_100ms_loop();
		sch_1s_loop();
		sch_tcb_loop();
	}
	return 0;
}


/*The End of r_func.c */
