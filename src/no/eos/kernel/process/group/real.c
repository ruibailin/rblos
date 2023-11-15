
/*------------------------------------
 * real.c
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
//static	int real_head=0;

void grp_add_real_pro(int pno);
void grp_add_real_pro(int pno)
{
	int real_head;
	real_head=grp_get_head(REAL_PROC);
	if(pno == real_head)
		return;
	if(real_head == 0)
		grp_set_head(REAL_PROC,pno);				//first process
	else
		grp_add_pro(real_head,pno);
}

void grp_del_real_pro(int pno);
void grp_del_real_pro(int pno)
{
	int real_head;
	real_head=grp_get_head(REAL_PROC);
	if(pno == real_head)
	{
		grp_set_head(REAL_PROC,pno);
		return;
	}
	grp_del_pro(pno);
}

void grp_ini_real_pro(void);
void grp_ini_real_pro()
{
	int i,j;
	for(i=1;i<MAX_PAT_NUM;i++)
	{
		j=get_pat_tno(i);
		if(j==REAL_PROC)
		{
			grp_add_real_pro(i);
		}
	}
}


void grp_run_real_pro(void);
void grp_run_real_pro()
{
	int run;
	int real_head;
	run_pat_entry(0,0x0L);			//process 0 is system special process`
	real_head=grp_get_head(REAL_PROC);
	if(real_head == 0)
		return;						//no real process
	run = real_head;
	for(;;)							//schedule all real process in every main loop;
	{
		run_pat_entry(run,0x0L);
		run=grp_get_pro(run);
		if(run == real_head)
			return;
	}
}

/*================================================================*/

/* end of real.c */
