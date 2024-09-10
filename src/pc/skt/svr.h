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


#ifndef SKT_SVR_H_
#define SKT_SVR_H_

extern int rbl_svr_init_skt(int type,int port);		//type=1:TCP;type=2:UDP
extern int rbl_svr_conn_skt(int type,int skt_fd,void *clt_info);
extern void rbl_svr_free_skt(int type,int skt_fd,int cnct_fd);
extern int rbl_svr_recv_skt(int type,int skt_fd,int cnct_fd,char *frm,int size,void *clt_info);
extern int rbl_svr_send_skt(int type,int skt_fd,int cnct_fd,char *frm,int size,void *clt_info);
extern void rbl_svr_set_nonblock(int type,int skt_fd);
extern void rbl_svr_set_block(int type,int skt_fd);
#endif 
/* end of svr.h */
