
/*------------------------------------
 * r_msg.h
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


#ifndef SRC_EOS_KERNEL_MESSAGE_R_MSG_H_
#define SRC_EOS_KERNEL_MESSAGE_R_MSG_H_
/*================================================================*/
#define   EventIdleQHead    0
#define	  EventBusyQHead	1

extern	void	ini_msg_list(void);
extern	int		get_msg_idle(int s,int eve,int len);
extern	void	set_msg_busy(int node,int d,void *out);
extern	int		get_msg_arrived(void);
extern	void	free_msg_arrived(int node);
extern	int		get_msg_dest(int node);
extern	int		get_msg_sour(int node);
extern	int		get_msg_event(int node);
extern	int		get_msg_length(int node);
extern	void	*get_msg_body(int node);

/*================================================================*/
#endif
/* end of r_msg.h */
