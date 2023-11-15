
/*------------------------------------
 * schedule.c
 * Create:  2023-02-21
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */

#include "1imp.h"
#include "r_tcb.h"
/*================================================================*/
int knl_this_tim=0;
void	knl_ini_tim(void);
void	knl_ini_tim()
{
	ini_tcb_list();
}

extern	void	run_pat_entry(int  pno,void *in);
int	knl_run_tim(void);
int	knl_run_tim()
{
	int tcb;
	int pno;

	tcb=get_tcb_arrived();
	if(tcb==TimerIdleQHead)
		return 0;
	if(tcb==TimerBusyQHead)
		return 0;

	knl_this_tim=tcb;				//schedule only one timer per main loop
	pno=get_tcb_pno(tcb);
	run_pat_entry(pno,0x0l);
	free_tcb_arrived(tcb);
	knl_this_tim=0;
	return 1;
}

/*================================================================*/

/* end of schedule.c */
