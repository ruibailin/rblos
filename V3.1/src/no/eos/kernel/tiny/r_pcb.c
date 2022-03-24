
/*------------------------------------
 * r_pcb.c
 * Create:  2021-10-16
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
#if EOS_TINY_MODE
/*================================================================*/
#include	"../r_pat.h"
#include	"../r_msg.h"

/*================================================================*/
typedef struct{
	unsigned char   state;
	unsigned char   event;
	unsigned char   timer[4];
}PCB;

/*------------------------------------*/
#define MAX_PCB_NUM	MAX_PAT_NUM
static	PCB	 PCBPool[MAX_PCB_NUM];

/*===========================================================================*/
/*------------------------------------*/
int	get_pcb_state(int pcb);
int	get_pcb_state(int pcb)
{
	int state;
	state=((int)PCBPool[pcb].state)&0xff;
	return(state);
}
/*------------------------------------*/
void	set_pcb_state(int pcb,int ss);
void	set_pcb_state(int pcb,int ss)
{
	PCBPool[pcb].state=(unsigned char)ss;
}
/*------------------------------------*/
int	get_pcb_event(int pcb);
int	get_pcb_event(int pcb)
{
	int event;
	event=((int)PCBPool[pcb].event)&0xff;
	return(event);
}
/*------------------------------------*/
void	set_pcb_event(int pcb,int event);
void	set_pcb_event(int pcb,int event)
{
	PCBPool[pcb].event=(unsigned char)event;
}
/*------------------------------------*/
int	get_pcb_timer(int pcb,int ptno);
int	get_pcb_timer(int pcb,int ptno)
{
	int timer;
	timer=((int)PCBPool[pcb].timer[ptno])&0xff;
	return(timer);
}
/*------------------------------------*/
void	set_pcb_timer(int pcb,int ptno,int ttno);
void	set_pcb_timer(int pcb,int ptno,int ttno)
{
	PCBPool[pcb].timer[ptno]=(unsigned char)ttno;
}

/*------------------------------------*/
void run_pcb_node(int pcb);
void run_pcb_node(int pcb)
{
	int event;
	void *in;
	event=((int)PCBPool[pcb].event)&0xff;
	in=get_msg_body(event);
	run_pat_entry(pcb,in);
}

/*------------------------------------*/
void ini_pcb_list(int pcb,int task);
void ini_pcb_list(int pcb,int task)
{
	int i;
	for(i=0;i<MAX_PCB_NUM;i++)
	{
		PCBPool[i].event = 0;
		PCBPool[i].state = 0;
	}

}

extern	int	sys_pno;
void run_pcb_list(void);
void run_pcb_list(void)
{
	int i;

	for(i=0;i<MAX_PCB_NUM;i++)
	{
		sys_pno = i;
		run_pat_entry(i,(void *)0L);
	}
}

/*================================================================*/
#endif
/* end of r_pcb.c */
