
/*------------------------------------
 * r_func.c
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
extern int	knl_this_pno;
/*================================================================*/
#include "./runtime/r_pcb.h"
/*------------------------------------*/
int	EOS_SELF(void);
int	EOS_SELF()
{
	return(knl_this_pno);
}
/*------------------------------------*/
int	EOS_STATE(void);
int	EOS_STATE()
{
	int ss;
	ss=get_pcb_state(knl_this_pno);
	return(ss);
}
/*------------------------------------*/
void EOS_NEXT(int ss);
void EOS_NEXT(int ss)
{
	set_pcb_state(knl_this_pno,ss);
}
/*================================================================*/
extern int knl_this_msg;
extern int knl_this_tim;
#include "./message/r_msg.h"
#include "./timer/r_tcb.h"
/*------------------------------------*/
#include "../user/eos_event.h"

int	EOS_EVENT(void);
int	EOS_EVENT()
{
	int event;
	int pno,tno;
	if(knl_this_msg!=0)
	{
		event=get_msg_event(knl_this_msg);
		return(event);
	}
	if(knl_this_tim!=0)
	{
		pno=get_tcb_pno(knl_this_tim);
		if(pno!=knl_this_pno)
			return 0;
		tno=get_tcb_tno(knl_this_tim);
		tno += EOS_TIMER0_EVENT;
		return(tno);
	}
	return 0;
}
/*------------------------------------*/
int	EOS_LENGTH(void);
int	EOS_LENGTH()
{
	int length;
	if(knl_this_msg==0)
		return 0;

	length=get_msg_length(knl_this_msg);
	return(length);
}
/*------------------------------------*/
int	EOS_SENDER(void);
int	EOS_SENDER()
{
	int sour;

	if(knl_this_msg==0)
		return 0;
	sour=get_msg_sour(knl_this_msg);
	return(sour);
}

/*------------------------------------*/
void	EOS_ASEND(int dd,int ee,int ll,void *in);
void	EOS_ASEND(int dd,int ee,int ll,void *in)
{
	int node;
	node=get_msg_idle(knl_this_pno,ee,ll);
	set_msg_busy(node,dd,in);
}
/*================================================================*/
/*------------------------------------*/
void EOS_SET(int tno,int ll);
void EOS_SET(int tno,int ll)
{
	int node;
	ll /= 10;
	if(ll==0)
		ll=1;
	ll *= 10;

	node=get_pcb_timer(knl_this_pno,tno);
	if(node != 0)							//repeat set timer
		reset_node_tcb(node);

	node=get_node_tcb(tno,knl_this_pno);
	set_pcb_timer(knl_this_pno,tno,node);
	set_node_tcb(node,ll);
}
/*------------------------------------*/
void EOS_KILL(int tno);
void EOS_KILL(int tno)
{
	int node;
	node=get_pcb_timer(knl_this_pno,tno);
	reset_node_tcb(node);
	set_pcb_timer(knl_this_pno,tno,0);
}

/*------------------------------------*/
void *eos_get_data(void);
void *eos_get_data()
{
	void *data;
	data=get_pcb_data(knl_this_pno);
	return data;
}

void eos_set_data(void *data);
void eos_set_data(void *data)
{
	set_pcb_data(knl_this_pno,data);
}


int eos_get_parent_pid(void);
int eos_get_parent_pid()
{
	int	pid;
	pid=get_pcb_parent(knl_this_pno);
	return pid;
}
/*================================================================*/

/* end of r_func.c */
