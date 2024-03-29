/*---------------------------
 * svr.h
 *  Created on: Aug 10, 2017
 *      Author: Bailin Rui
 *---------------------------
 *
 *
 *
 *
 *---------------------------
 */


#ifndef SKT_TCP_SVR_H_
#define SKT_TCP_SVR_H_

extern void tcp_svr_init_skt(void);		//type=1:TCP;type=2:UDP
extern void tcp_svr_free_skt(void);
extern int tcp_svr_recv_skt(char *frm,int size);
extern int tcp_svr_send_skt(char *frm,int size);
extern void tcp_svr_set_nonblock(void);
extern void tcp_svr_set_block(void);
#endif 
/* end of svr.h */
