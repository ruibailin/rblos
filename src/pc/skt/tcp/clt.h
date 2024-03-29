/*---------------------------
 * clt.h
 *  Created on: Aug 11, 2017
 *      Author: Bailin Rui
 *---------------------------
 *
 *
 *
 *
 *---------------------------
 */


#ifndef SKT_TCP_CLT_H_
#define SKT_TCP_CLT_H_

extern void tcp_clt_init_skt(void);		//type=1:TCP;type=2:UDP
extern void tcp_clt_free_skt(void);
extern int tcp_clt_send_skt(char *frm,int size);
extern int tcp_clt_recv_skt(char *frm,int size);
extern int tcp_clt_init_add(char *ip_addr);
extern void tcp_clt_set_nonblock(void);
extern void tcp_clt_set_block(void);
#endif 
/* end of clt.h */
