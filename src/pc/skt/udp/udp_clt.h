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


#ifndef SKT_rbl_udp_clt_H_
#define SKT_rbl_udp_clt_H_

extern int rbl_udp_clt_init_skt(char *svr_ip,int port);		//type=1:TCP;type=2:UDP
extern void rbl_udp_clt_free_skt(int skt_fd);
extern int rbl_udp_clt_send_skt(int skt_fd,char *frm,int size);
extern int rbl_udp_clt_recv_skt(int skt_fd,char *frm,int size);
extern void rbl_udp_clt_set_nonblock(int skt_fd);
extern void rbl_udp_clt_set_block(int skt_fd);
#endif 
/* end of clt.h */
