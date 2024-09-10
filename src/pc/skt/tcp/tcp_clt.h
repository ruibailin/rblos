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


#ifndef SKT_rbl_tcp_clt_H_
#define SKT_rbl_tcp_clt_H_

extern int rbl_tcp_clt_init_skt(char *ip,int port);		//type=1:TCP;type=2:UDP
extern void rbl_tcp_clt_free_skt(int fd);
extern int rbl_tcp_clt_send_skt(int fd,char *frm,int size);
extern int rbl_tcp_clt_recv_skt(int fd,char *frm,int size);
extern void rbl_tcp_clt_set_nonblock(int fd);
extern void rbl_tcp_clt_set_block(int fd);
#endif 
/* end of clt.h */
