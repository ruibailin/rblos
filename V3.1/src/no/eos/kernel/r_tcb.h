
/*------------------------------------
 * r_tcb.h
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
#ifndef EOS_KERNEL_R_TCB_H_
#define EOS_KERNEL_R_TCB_H_
/*================================================================*/
extern	void	ini_tcb_list(void);
extern	int		get_node_tcb(int tno,int pno);
extern	void	set_node_tcb(int node,int len);
extern	void	reset_node_tcb(int node);
extern	void	run_tcb_list(void);
extern	int		get_tcb_arrived(void);
extern	void	free_tcb_arrived(int node);
extern	int		get_tcb_tno(int node);
extern	int		get_tcb_pno(int node);
/*================================================================*/
#endif
/* end of r_tcb.h */
