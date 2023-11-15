
/*------------------------------------
 * schedule.c
 * Create:  2021-10-17
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */

#include "0ctr.h"

/*================================================================*/
/*================================================================*/
#include "./kernel/2exp.h"
extern	int	sys_pno;
/*================================================================*/

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


/*================================================================*/
void eos_time(void);
void eos_time()
{
	run_tcb_list();
}


void eos_main();
void eos_main()
{

	int ret1,ret2;
	ini_tcb_list();
	ini_msg_list();
	ini_pat_table();
	ini_pcb_list();

	run_pcb_list();

	for(;;)
	{
		ret1 = sch_one_msg();
		ret2 = sch_one_tcb_msg();
		ret1 |= ret2;
		if(ret1)
			continue;
		sys_pno = 0;		//To Run idle process
		run_pat_entry(0,(void *)0L);
	}
}

int no_main(int argc, char **argv);
int no_main(int argc, char **argv)
{
	eos_main();
	return 0;
}
/*================================================================*/

/* end of schedule.c */
