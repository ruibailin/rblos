
/*------------------------------------
 * slot.c
 * Create:  2023-02-17
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 * Schedule by time slot, wait to implement in future
 *
 *
 *
 *------------------------------------
 */

#include "1imp.h"
#include "queue.h"
/*================================================================*/
//static	int slot_head=0;

void grp_add_slot_pro(int pno);
void grp_add_slot_pro(int pno)
{
	int slot_head;
	slot_head=grp_get_head(SLOT_PROC);
	if(pno == slot_head)
		return;
	if(slot_head == 0)
		grp_set_head(SLOT_PROC,pno);			//first process
	else
		grp_add_pro(slot_head,pno);
}

void grp_del_slot_pro(int pno);
void grp_del_slot_pro(int pno)
{
	int slot_head;
	slot_head=grp_get_head(SLOT_PROC);
	if(pno == slot_head)
	{
		grp_set_head(SLOT_PROC,0);
		return;
	}
	grp_del_pro(pno);
}

void grp_ini_slot_pro(void);
void grp_ini_slot_pro()
{
	int i,j;
	for(i=1;i<MAX_PAT_NUM;i++)
	{
		j=get_pat_tno(i);
		if(j==SLOT_PROC)
		{
			grp_add_slot_pro(i);
		}
	}
}


int	grp_run_slot_pro(void);
int	grp_run_slot_pro()
{
	int run;
	int slot_head;
	slot_head=grp_get_head(SLOT_PROC);
	if(slot_head == 0)
		return 0;						//no time slot process
	run=grp_get_pro(slot_head);
//	run_pat_entry(run,0x0L);
	slot_head=run;				//only schedule in its time slot;
	return 1;
}

/*================================================================*/

/* end of slot.c */
