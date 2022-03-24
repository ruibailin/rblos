/*
 * r_pcb.c
 *
 *  Created on: Apr 13, 2021
 *      Author: steve
 */


#include "0ctr.h"
/*================================================================*/
#include	"r_pat.h"
#include	"r_msg.h"

/*================================================================*/
typedef struct{
	int   state;
	int   event;
	int	  stack;
	int   timer[8];
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
	state=PCBPool[pcb].state;
	return(state);
}
/*------------------------------------*/
void	set_pcb_state(int pcb,int ss);
void	set_pcb_state(int pcb,int ss)
{
	PCBPool[pcb].state=ss;
}
/*------------------------------------*/
int	get_pcb_event(int pcb);
int	get_pcb_event(int pcb)
{
	int event;
	event=PCBPool[pcb].event;
	return(event);
}
/*------------------------------------*/
void	set_pcb_event(int pcb,int ee);
void	set_pcb_event(int pcb,int ee)
{
	PCBPool[pcb].event=ee;
}
/*------------------------------------*/
int	get_pcb_timer(int pcb,int tno);
int	get_pcb_timer(int pcb,int tno)
{
	int timer;
	timer=PCBPool[pcb].timer[tno];
	return(timer);
}
/*------------------------------------*/
void	set_pcb_timer(int pcb,int tno,int tt);
void	set_pcb_timer(int pcb,int tno,int tt)
{
	PCBPool[pcb].timer[tno]=tt;
}

/*------------------------------------*/
void run_pcb_node(int pcb);
void run_pcb_node(int pcb)
{
	int ee;
	void *in;
	void ( *process)(void *in);
	ee=PCBPool[pcb].event;
	in=get_msg_body(ee);
	process=get_pat_entry(pcb);
	process(in);
}

/*------------------------------------*/
void ini_pcb_list(int pcb,int task);
void ini_pcb_list(int pcb,int task)
{
	int i;
	for(i=0;i<MAX_PCB_NUM;i++)
	{
		PCBPool[pcb].event = 0;
		PCBPool[pcb].state = 0;
	}

}

extern	int	sys_pno;
void run_pcb_list(void);
void run_pcb_list(void)
{
	int i;
	void ( *process)(void *in);

	for(i=0;i<MAX_PCB_NUM;i++)
	{
		sys_pno = i;
		process=get_pat_entry(i);
		process((void *)0L);
	}
}
/*================================================================*/
/* end of r_pcb.c */
