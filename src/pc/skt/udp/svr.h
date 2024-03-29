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


#ifndef SKT_UDP_SVR_H_
#define SKT_UDP_SVR_H_

extern void udp_svr_init_skt(void);		//type=1:TCP;type=2:UDP
extern void udp_svr_free_skt(void);
extern int udp_svr_recv_skt(char *frm,int size);
extern int udp_svr_send_skt(char *frm,int size);
extern void udp_svr_set_nonblock(void);
extern void udp_svr_set_block(void);
#endif 
/* end of svr.h */
