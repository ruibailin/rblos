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


#ifndef SVR_H_
#define SVR_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

extern int rbl_svr_init_skt(int type,int port);		//type=1:TCP;type=2:UDP
extern int rbl_svr_conn_skt(int type,int skt_fd,struct sockaddr *addr);
extern void rbl_svr_free_skt(int type,int skt_fd,int cnct_fd);
extern int rbl_svr_recv_skt(int type,int skt_fd,int cnct_fd,char *frm,int size,struct sockaddr *addr);
extern int rbl_svr_send_skt(int type,int skt_fd,int cnct_fd,char *frm,int size,struct sockaddr *addr);
extern void rbl_svr_set_nonblock(int type,int skt_fd);
extern void rbl_svr_set_block(int type,int skt_fd);
#endif 
/* end of svr.h */
