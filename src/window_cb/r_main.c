
/*windows consol GUI*/

#include "r_msg.h"
#include "r_tcb.h"
#include "r_pat.h"
#include "r_pcb.h"

extern	int	sys_pno;
/*================================================================*/
/*----------------------------------------*/
static	void	sch_msg_loop(void);
static	void	sch_msg_loop()
{
	int	node;

	node=get_msg_arrived();
	if(node==0)	return;

	sys_pno=get_msg_dest(node);
	set_pcb_event(sys_pno,node);	//save event ptr
	run_pcb_node(sys_pno);
	free_msg_arrived(node);
}
	

/*----------------------------------------*/
static	short	int	c_10ms=0;
static	void	sch_10ms_loop(void);
static	void	sch_10ms_loop()
{
	int	next;
	
	c_10ms++;
	
	run_tcb_list();
	next=get_pcb_next(1);
	for(;;)
	{
		if(next == 1)	break;
		sys_pno=next;
		run_pcb_node(sys_pno);
		next=get_pcb_next(sys_pno);
	}
}
/*----------------------------------------*/
static	short	int	c_100ms=0;
static	void	sch_100ms_loop(void);
static	void	sch_100ms_loop()
{
	int	next;
	if(c_10ms <10) return;
	
	c_10ms=0;
	c_100ms++;
	next=get_pcb_next(2);
	for(;;)
	{
		if(next == 2)	break;
		sys_pno=next;
		run_pcb_node(sys_pno);
		next=get_pcb_next(sys_pno);
	}
}	
/*----------------------------------------*/
static	long	c_1s=0;
static	void	sch_1s_loop(void);
static	void	sch_1s_loop()
{
	int	next;
	if(c_100ms <10) return;
	
	c_100ms=0;
	c_1s++;
	next=get_pcb_next(3);
	for(;;)
	{
		if(next == 3)	break;
		sys_pno=next;
		run_pcb_node(sys_pno);
		next=get_pcb_next(sys_pno);
	}
}	
/*----------------------------------------*/
extern	void	send_ret(void);
static	void	sch_tcb_loop(void);
static	void	sch_tcb_loop()
{
	int	next,node;
	int dd,ee;
	next=get_tcb_arrived();
	for(;;)
	{
		if(next == 0)	break;
		dd=get_tcb_pno(next);
		ee=get_tcb_tno(next);
		node=get_idle_msg(0,ee,0);
		set_busy_msg(node,dd,(void *)0L);
		send_ret();

		free_tcb_arrived(next);
		next=get_tcb_arrived();
	}
}	
/*--------------------------------------*/
static	void	run_pro_first(void);
static	void	run_pro_first()
{
	int next;
	next=get_pcb_next(0);
	for(;;)
	{
		if(next == 0)	break;
		sys_pno=next;
		run_pcb_node(sys_pno);
		next=get_pcb_next(sys_pno);
	}
}

/*================================================================*/
extern	ini_test_proc(void);
/*--------------------------------------*/
void	main_ini(void);
void	main_ini()
{
	ini_tcb_list();
	ini_msg_list();
	
	ini_test_proc();

	ini_pcb_list();

	run_pro_first();
}
/*--------------------------------------*/
void	main_msg(void);
void	main_msg()
{
		sch_msg_loop();
}
/*--------------------------------------*/
void	main_10ms(void);
void	main_10ms()
{
		sch_10ms_loop();
		sch_100ms_loop();
		sch_1s_loop();
		sch_tcb_loop();
}
/*The End of r_func.c */