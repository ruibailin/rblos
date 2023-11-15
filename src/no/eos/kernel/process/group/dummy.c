
/*------------------------------------
 * dummy.c
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
//static	int dum_head=0;

void grp_add_dum_pro(int pno);
void grp_add_dum_pro(int pno)
{
	int dum_head;
	dum_head=grp_get_head(DUM_PROC);
	if(pno == dum_head)
		return;
	if(dum_head == 0)
		grp_set_head(DUM_PROC,pno);			//first process
	else
		grp_add_pro(dum_head,pno);
}

void grp_del_dum_pro(int pno);
void grp_del_dum_pro(int pno)
{
	int dum_head;
	dum_head=grp_get_head(DUM_PROC);
	if(pno == dum_head)
	{
		dum_head=0;
		return;
	}
	grp_del_pro(pno);
}

void grp_ini_dum_pro(void);
void grp_ini_dum_pro()
{
	int i,j;
	for(i=1;i<MAX_PAT_NUM;i++)
	{
		j=get_pat_tno(i);
		if(j==DUM_PROC)
		{
			grp_add_dum_pro(i);
		}
	}
}

int  grp_get_dum_pro(void);
int  grp_get_dum_pro()
{
	int pno;
	int dum_head;
	dum_head=grp_get_head(DUM_PROC);
	if(dum_head == 0)
	{
		knl_print("no pat resource\n");
		knl_panic();
		return 0;
	}
	pno=grp_get_pro(dum_head);
	if(pno == dum_head)
		grp_set_head(DUM_PROC,0);			//Only one node, queue is empety

	return pno;
}

/*================================================================*/

/* end of dummy.c */
