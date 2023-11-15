#ifndef _r_pcb_h
#define _r_pcb_h

/*------------------------------------*/
extern	int		get_pcb_state(int pcb);
extern	void	set_pcb_state(int pcb,int ss);
extern	int		get_pcb_event(int pcb);
extern	void	set_pcb_event(int pcb,int ee);
extern	int		get_pcb_timer(int pcb,int tno);
extern	void	set_pcb_timer(int pcb,int tno,int tt);
extern	void	ini_pcb_list(void);
extern	void	run_pcb_node(int pcb);
extern	int		get_pcb_next(int root);
extern	void	set_pcb_task(int pcb,int task);

#endif
/*End of r_pcb.h*/

