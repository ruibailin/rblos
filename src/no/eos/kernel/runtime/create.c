
/*------------------------------------
 * create.c
 * Create:  2023-05-18
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
#include "../process/basic/pat.h"
#include "../process/basic/r_pat.h"
#include "../process/group/2exp.h"
#include "../message/r_msg.h"
#include "r_pcb.h"
/*================================================================*/
int create_pcb(char *name,void (*entry)(void *),int type,int attr);
int create_pcb(char *name,void (*entry)(void *),int type,int attr)
{
	int pno;
	int node;
	if(type==DUM_PROC)
		return 0;
	if(type>MAX_TYPE_NUM-1)
		return 0;
	pno=grp_get_next_pro(DUM_PROC,0);
	if(pno==0)
		return 0;
	grp_del_next_pro(DUM_PROC,pno);
	switch(type)
	{
	case	IDLE_PROC:
		break;
	case	SLOT_PROC:
		break;
	case	MSG_PROC:
		node=get_msg_idle(knl_this_pno,0,0);
		set_msg_busy(node,pno,0x0L);
		break;
	case	TIME_PROC:
		if(attr==0)
			attr=1;
		break;
	case	REAL_PROC:
		break;
	default:
		break;
	}
	set_pat_name(pno,name);
	set_pat_entry(pno,entry);
	set_pat_tno(pno,type);
	set_pat_attr(pno,attr);
	grp_add_next_pro(type,pno);
	set_pcb_parent(pno,knl_this_pno);
	return pno;
}

int eos_create_real(char *name,void (*entry)(void *));
int eos_create_real(char *name,void (*entry)(void *))
{
	int ret;
	ret=create_pcb(name,entry,REAL_PROC,0);
	return ret;
}

int eos_create_time(char *name,void (*entry)(void *),int interval);
int eos_create_time(char *name,void (*entry)(void *),int interval)
{
	int ret;
	ret=create_pcb(name,entry,TIME_PROC,interval);
	return ret;
}

int eos_create_idle(char *name,void (*entry)(void *));
int eos_create_idle(char *name,void (*entry)(void *))
{
	int ret;
	ret=create_pcb(name,entry,IDLE_PROC,0);
	return ret;
}
/*================================================================*/
/* end of create.c */
