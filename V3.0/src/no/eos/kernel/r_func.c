
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
int	sys_pno=0;
/*================================================================*/
#include "r_msg.h"
#include "r_pat.h"
#include "r_tcb.h"
#include "r_pcb.h"
/*------------------------------------*/
int	SELF(void);
int	SELF()
{
	return(sys_pno);
}
/*------------------------------------*/
int	STATE(void);
int	STATE()
{
	int ss;
	ss=get_pcb_state(sys_pno);
	return(ss);
}
/*------------------------------------*/
void NEXT_STATE(int ss);
void NEXT_STATE(int ss)
{
	set_pcb_state(sys_pno,ss);
}
/*================================================================*/
/*------------------------------------*/
int	EVENT(void);
int	EVENT()
{
	int node;
	int event;
	node=get_pcb_event(sys_pno);
	event=get_msg_event(node);
	return(event);
}
/*------------------------------------*/
int	LENGTH(void);
int	LENGTH()
{
	int node;
	int length;
	node=get_pcb_event(sys_pno);
	length=get_msg_length(node);
	return(length);
}
/*------------------------------------*/
int	SENDER(void);
int	SENDER()
{
	int node;
	int sour;
	node=get_pcb_event(sys_pno);
	sour=get_msg_sour(node);
	return(sour);
}

/*------------------------------------*/
void	ASEND(int dd,int ee,int ll,void *in);
void	ASEND(int dd,int ee,int ll,void *in)
{
	int node;
	node=get_idle_msg(sys_pno,ee,ll);
	set_busy_msg(node,dd,in);
}
/*================================================================*/
/*------------------------------------*/
void SET(int tno,int ll);
void SET(int tno,int ll)
{
	int node;
	node=get_node_tcb(tno,sys_pno);
	set_pcb_timer(sys_pno,tno,node);
	set_node_tcb(node,ll);
}
/*------------------------------------*/
void KILL(int tno);
void KILL(int tno)
{
	int node;
	node=get_pcb_timer(sys_pno,tno);
	reset_node_tcb(node);
}

/*================================================================*/

/* end of r_func.c */
