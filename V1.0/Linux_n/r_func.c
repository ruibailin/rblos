
/*promotive*/

#include "r_msg.h"
#include "r_tcb.h"
#include "r_pat.h"
#include "r_pcb.h"
#include "r_sema.h"
#include "r_thrd.h"
#include "r_lock.h"


/*========================process related=========================================*/

/*------------------------------------*/
int	SELF(void);
int	SELF()
{
	int	sys_pno;
	sys_pno=get_sys_pno();
	return(sys_pno);
}
/*------------------------------------*/
int	STATE(void);
int	STATE()
{
	int ss;
	int	sys_pno;
	sys_pno=get_sys_pno();
	ss=get_pcb_state(sys_pno);
	return(ss);
}
/*------------------------------------*/
void NEXT_STATE(int ss);
void NEXT_STATE(int ss)
{
	int	sys_pno;
	sys_pno=get_sys_pno();
	set_pcb_state(sys_pno,ss);
}
/*========================message related=========================================*/
/*------------------------------------*/
int	EVENT(void);
int	EVENT()
{
	int node;
	int event;
	int	sys_pno;
	sys_pno=get_sys_pno();
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
	int	sys_pno;
	sys_pno=get_sys_pno();
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
	int	sys_pno;
	sys_pno=get_sys_pno();
	node=get_pcb_event(sys_pno);
	sour=get_msg_sour(node);
	return(sour);
}

/*------------------------------------*/
void	ASEND(int dd,int ee,int ll,void *in);
void	ASEND(int dd,int ee,int ll,void *in)
{
	int node;
	int	sys_pno;
	sys_pno=get_sys_pno();
	lock_lock();
	node=get_idle_msg(sys_pno,ee,ll);
	set_busy_msg(node,dd,in);
	unlock_lock();
}
/*========================Timer  related=========================================*/
/*------------------------------------*/
void SET(int tno,int ll);
void SET(int tno,int ll)
{
	int node;
	int	sys_pno;
	sys_pno=get_sys_pno();
	lock_lock();
	node=get_node_tcb(tno,sys_pno);
	set_pcb_timer(sys_pno,tno,node);
	set_node_tcb(node,ll);
	unlock_lock();
}
/*------------------------------------*/
void KILL(int tno);
void KILL(int tno)
{
	int node;
	int	sys_pno;
	sys_pno=get_sys_pno();
	lock_lock();
	node=get_pcb_timer(sys_pno,tno);
	reset_node_tcb(node);
	unlock_lock();
}

/*The End of r_func.c */