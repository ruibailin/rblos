
/*linux consol GUI*/

#include "r_msg.h"
#include "r_tcb.h"
#include "r_pat.h"
#include "r_pcb.h"
#include "r_sema.h"
#include "r_thrd.h"
#include "r_lock.h"


/*================================================================*/

/*----------------------------------------*/
void	sch_10ms_loop(void *in);
void	sch_10ms_loop(void *in)
{
	int	next,node;
	int dd,ee;

	lock_lock();
	run_tcb_list();
	next=get_tcb_arrived();
	unlock_lock();
	if(next == 0)	return;
	dd=get_tcb_pno(next);
	ee=get_tcb_tno(next);

	lock_lock();
	node=get_idle_msg(0,ee,0);
	set_pcb_msg(node,dd,(void *)0L);
	unlock_lock();
	post_sema(dd);
	lock_lock();
	free_tcb_arrived(next);
	unlock_lock();
}


/*================================================================*/
#define		PAT_LIST_NUM		4
#define		MAX_PAT_NUM		32
#define	MAX_NODE_NUM	PAT_LIST_NUM+MAX_PAT_NUM
/*------------------------------------*/
void ini_user_proc(void);
void ini_user_proc(void)
{
	int ii;
	int tno;
	int node;
	for(ii=0;ii<MAX_NODE_NUM;ii++)
	{
		tno=get_pat_tno(ii);
		if(tno != 0)
			continue;
		node=get_idle_msg(0,0,0);
		set_pcb_msg(node,ii,(void *)0L);
		post_sema(ii);
	}
 }

/*================================================================*/
extern	ini_test_proc(void);

int	main(void);
int	main()
{
	ini_tcb_list();
	ini_pcb_msg();
	ini_pcb_list();
	ini_lock();
	init_sema();

	set_pat_tno(0,1);
	set_pat_entry(0,&sch_10ms_loop);
	
	ini_test_proc();

	ini_user_proc();
	ini_linux_thread();

	for(;;)	
		wait_sema(0);

	return 0;
}


/*The End of r_func.c */
