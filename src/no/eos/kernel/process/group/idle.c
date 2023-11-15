
/*------------------------------------
 * idle.c
 * Create:  2023-02-17
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
#include "queue.h"
/*================================================================*/
//static	int idle_head=0;

void grp_add_idle_pro(int pno);
void grp_add_idle_pro(int pno)
{
	int idle_head;
	idle_head=grp_get_head(IDLE_PROC);
	if(pno == idle_head)
		return;
	if(idle_head == 0)
		grp_set_head(IDLE_PROC,pno);			//first process
	else
		grp_add_pro(idle_head,pno);
}

void grp_del_idle_pro(int pno);
void grp_del_idle_pro(int pno)
{
	int idle_head;
	idle_head=grp_get_head(IDLE_PROC);
	if(pno == idle_head)
	{
		grp_set_head(IDLE_PROC,0);
		return;
	}
	grp_del_pro(pno);
}

void grp_ini_idle_pro(void);
void grp_ini_idle_pro()
{
	int i,j;
	for(i=1;i<MAX_PAT_NUM;i++)
	{
		j=get_pat_tno(i);
		if(j==IDLE_PROC)
		{
			grp_add_idle_pro(i);
		}
	}
}

static  int run_idle=0;
void	grp_run_idle_pro(void);
void	grp_run_idle_pro()
{
	int idle_head;
	idle_head=grp_get_head(IDLE_PROC);
	if(idle_head == 0)
		return;						//no idle process
	if(run_idle == 0)
		run_idle=idle_head;
	run_pat_entry(run_idle,0x0L);	//every time,only schedule one idle process;
	run_idle=grp_get_pro(run_idle); //get process to run next time
}

/*================================================================*/

/* end of idle.c */
