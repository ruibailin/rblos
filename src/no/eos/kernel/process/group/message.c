
/*------------------------------------
 * message.c
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
//static	int msg_head=0;

void grp_add_msg_pro(int pno);
void grp_add_msg_pro(int pno)
{
	int msg_head;
	msg_head=grp_get_head(MSG_PROC);
	if(pno == msg_head)
		return;
	if(msg_head == 0)
		grp_set_head(MSG_PROC,pno);			//first process
	else
		grp_add_pro(msg_head,pno);
}

void grp_del_msg_pro(int pno);
void grp_del_msg_pro(int pno)
{
	int msg_head;
	msg_head=grp_get_head(MSG_PROC);
	if(msg_head==0)
		return;
	if(pno == msg_head)
		grp_set_head(MSG_PROC,0);
	else
		grp_del_pro(pno);
}

void grp_ini_msg_pro(void);
void grp_ini_msg_pro()
{
	int i,j;
	for(i=1;i<MAX_PAT_NUM;i++)
	{
		j=get_pat_tno(i);
		if(j==MSG_PROC)
		{
			grp_add_msg_pro(i);
		}
	}
}

void grp_run_msg_pro(void);	//only run one time
void grp_run_msg_pro()
{
	int run;
	int msg_head;
	msg_head=grp_get_head(MSG_PROC);
	if(msg_head == 0)
		return;						//no message-driven process
	run = msg_head;
	for(;;)							//run all message-driven process for initialization;
	{
		run_pat_entry(run,0x0L);
		run=grp_get_pro(run);
		if(run == msg_head)
			return;
	}
}
/*================================================================*/

/* end of message.c */
