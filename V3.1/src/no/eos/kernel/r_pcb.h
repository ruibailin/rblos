
/*------------------------------------
 * r_pcb.h
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
#ifndef EOS_KERNEL_R_PCB_H_
#define EOS_KERNEL_R_PCB_H_
/*================================================================*/
extern	int		get_pcb_state(int pcb);
extern	void	set_pcb_state(int pcb,int ss);

extern	int		get_pcb_event(int pcb);
extern	void	set_pcb_event(int pcb,int event);

extern	int		get_pcb_timer(int pcb,int ptno);
extern	void	set_pcb_timer(int pcb,int ptno,int ttno);

extern	void 	run_pcb_node(int pcb);
extern	void	ini_pcb_list(void);
extern	void	run_pcb_list(void);

/*================================================================*/
#endif
/* end of r_pcb.h */
