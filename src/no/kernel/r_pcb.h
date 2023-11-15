/*
 * r_pcb.h
 *
 *  Created on: Apr 13, 2021
 *      Author: steve
 */

#ifndef SRC_NO_KERNEL_R_PCB_H_
#define SRC_NO_KERNEL_R_PCB_H_
#include "1imp.h"
/*================================================================*/
extern	int		get_pcb_state(int pcb);
extern	void	set_pcb_state(int pcb,int ss);

extern	int		get_pcb_event(int pcb);
extern	void	set_pcb_event(int pcb,int ee);

extern	int		get_pcb_timer(int pcb,int tno);
extern	void	set_pcb_timer(int pcb,int tno,int tt);

extern	void 	run_pcb_node(int pcb);
extern	void	ini_pcb_list(void);
extern	void	run_pcb_list(void);
/*================================================================*/
#endif /* SRC_NO_KERNEL_R_PCB_H_ */
