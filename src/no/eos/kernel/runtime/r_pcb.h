
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


#ifndef SRC_EOS_KERNEL_RUNTIME_R_PCB_H_
#define SRC_EOS_KERNEL_RUNTIME_R_PCB_H_
/*================================================================*/
extern	int		get_pcb_state(int pcb);
extern	void	set_pcb_state(int pcb,int ss);

extern	void *get_pcb_data(int pcb);
extern	void	set_pcb_data(int pcb,void *data);

extern	int		get_pcb_parent(int pcb);
extern	void	set_pcb_parent(int pcb,int parent);

extern	int		get_pcb_timer(int pcb,int ptno);
extern	void	set_pcb_timer(int pcb,int ptno,int ttno);

extern  void    ini_pcb_list(void);

/*================================================================*/
#endif
/* end of r_pcb.h */
