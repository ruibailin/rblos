/*
 * r_msg.h
 *
 *  Created on: Apr 13, 2021
 *      Author: steve
 */

#ifndef SRC_NO_KERNEL_R_MSG_H_
#define SRC_NO_KERNEL_R_MSG_H_
#include "1imp.h"
/*================================================================*/
extern	void	ini_msg_list(void);
extern	int		get_idle_msg(int s,int eve,int len);
extern	void	set_busy_msg(int node,int d,void *out);
extern	int		get_msg_arrived(void);
extern	void	free_msg_arrived(int node);
extern	int		get_msg_dest(int node);
extern	int		get_msg_sour(int node);
extern	int		get_msg_event(int node);
extern	int		get_msg_length(int node);
extern	void	*get_msg_body(int node);
extern	void 	ini_pcb_msg(void);
extern	void 	set_pcb_msg(int node,int d,void *out);
extern	int		get_pcb_msg(int pcb);
/*================================================================*/
#endif /* SRC_NO_KERNEL_R_MSG_H_ */
