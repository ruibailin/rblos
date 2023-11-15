
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
#if EOS_SMALL_MODE
/*================================================================*/
#include	"../r_pat.h"
#include	"../r_msg.h"

/*================================================================*/
typedef struct{
	unsigned short   state;
	unsigned short   event;
	unsigned short   timer[8];
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
	state=((int)PCBPool[pcb].state)&0xffff;
	return(state);
}
/*------------------------------------*/
void	set_pcb_state(int pcb,int ss);
void	set_pcb_state(int pcb,int ss)
{
	PCBPool[pcb].state=(unsigned short)ss;
}
/*------------------------------------*/
int	get_pcb_event(int pcb);
int	get_pcb_event(int pcb)
{
	int event;
	event=((int)PCBPool[pcb].event)&0xffff;
	return(event);
}
/*------------------------------------*/
void	set_pcb_event(int pcb,int event);
void	set_pcb_event(int pcb,int event)
{
	PCBPool[pcb].event=(unsigned short)event;
}
/*------------------------------------*/
int	get_pcb_timer(int pcb,int ptno);
int	get_pcb_timer(int pcb,int ptno)
{
	int timer;
	timer=((int)PCBPool[pcb].timer[ptno])&0xffff;
	return(timer);
}
/*------------------------------------*/
void	set_pcb_timer(int pcb,int ptno,int ttno);
void	set_pcb_timer(int pcb,int ptno,int ttno)
{
	PCBPool[pcb].timer[ptno]=(unsigned short)ttno;
}

/*------------------------------------*/
void run_pcb_node(int pcb);
void run_pcb_node(int pcb)
{
	int event;
	void *in;
	event=((int)PCBPool[pcb].event)&0xffff;
	in=get_msg_body(event);
	run_pat_entry(pcb,in);
}

/*------------------------------------*/
void ini_pcb_list(void);
void ini_pcb_list()
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
