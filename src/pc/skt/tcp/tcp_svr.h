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


#ifndef SKT_rbl_tcp_svr_H_
#define SKT_rbl_tcp_svr_H_

extern int rbl_tcp_svr_init_skt(int port);		//type=1:TCP;type=2:UDP
extern int rbl_tcp_svr_conn_skt(int skt_fd,void *clt_info);
extern void rbl_tcp_svr_free_skt(int skt_fd,int cnct_fd);
extern int rbl_tcp_svr_recv_skt(int skt_fd,int cnct_fd,char *frm,int size);
extern int rbl_tcp_svr_send_skt(int skt_fd,int cnct_fd,char *frm,int size);
extern void rbl_tcp_svr_set_nonblock(int skt_fd);
extern void rbl_tcp_svr_set_block(int skt_fd);
#endif 
/* end of svr.h */
