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


#ifndef SKT_rbl_udp_svr_H_
#define SKT_rbl_udp_svr_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

extern int rbl_udp_svr_init_skt(int port);		//type=1:TCP;type=2:UDP
extern int rbl_udp_svr_conn_skt(int skt_fd);
extern void rbl_udp_svr_free_skt(int skt_fd,int cnct_fd);
extern int rbl_udp_svr_recv_skt(int skt_fd,char *frm,int size,struct sockaddr *addr);
extern int rbl_udp_svr_send_skt(int skt_fd,char *frm,int size,struct sockaddr *addr);
extern void rbl_udp_svr_set_nonblock(int skt_fd);
extern void rbl_udp_svr_set_block(int skt_fd);
#endif 
/* end of svr.h */
