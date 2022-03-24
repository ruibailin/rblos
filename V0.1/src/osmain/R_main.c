#include "rblstart.h"
#include "r_msg.h"
#include "r_pcb.h"
#include "r_tcb.h"
/*------------------------------------*/
void init_all(void);
void init_all()
{
	ini_self_msg();
	ini_pcb_queue();
	ini_tcb_queue();
	run_pcb_queue(ProIdleQueue);
	run_pcb_queue(Pro0msQueue);
	run_pcb_queue(Pro10msQueue);
	run_pcb_queue(Pro100msQueue);
	run_pcb_queue(Pro1000msQueue);
}
/*------------------------------------*/
void handle_10ms(void);
void handle_10ms()
{
   run_pcb_queue(Pro0msQueue); 				/*Real Time*/
}

/*------------------------------------*/
static WORD c100ms=0;
static WORD c1000ms=0;
void sch_proc(void);
void sch_proc()
{
	run_tcb_queue();
    send_tcb_msg(); 
	run_pcb_queue(Pro10msQueue);
	c100ms++;
	if (c100ms <10) return;
	c100ms=0;
	run_pcb_queue(Pro100msQueue); 	
	c1000ms++;
	if (c1000ms <10) return;
	c1000ms=0;
	run_pcb_queue(Pro1000msQueue); 	
}

/*------------------------------------*/
VFAR send_ret(void);
void sch_msg(void);
void sch_msg()
{
  run_pcb_msg();
}

/*------------------------------------*/

