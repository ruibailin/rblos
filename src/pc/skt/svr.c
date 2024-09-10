/*---------------------------
 * svr.c
 *  Created on: Aug 8, 2017
 *      Author: Bailin Rui
 *---------------------------
 *svr:server
 *skt:socket
 *cnct:connect
 *fd:file description
 *---------------------------
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "1imp.h"

/**************************************************/
int rbl_svr_init_skt(int type,int port);
int rbl_svr_init_skt(int type,int port)
{
	int fd;
	fd = -1;
	if(type==1)
	{
	    fd = rbl_tcp_svr_init_skt(port);
	}
	if(type==2)
	{
	    fd = rbl_udp_svr_init_skt(port);
	}
	return fd;
}

int rbl_svr_conn_skt(int type,int skt_fd);
int rbl_svr_conn_skt(int type,int skt_fd)
{
	int fd;
	fd = -1;
	if(type==1)
	{
	    fd = rbl_tcp_svr_conn_skt(skt_fd);
	}
	if(type==2)
	{
	    fd = rbl_udp_svr_conn_skt(skt_fd);
	}
	return fd;
}
/**************************************************/
void rbl_svr_free_skt(int type,int skt_fd,int cnct_fd);
void rbl_svr_free_skt(int type,int skt_fd,int cnct_fd)
{
	if(type==1)
	{
		rbl_tcp_svr_free_skt(skt_fd,cnct_fd);
	}
	if(type==2)
	{
		rbl_udp_svr_free_skt(skt_fd,cnct_fd);
	}
}

/**************************************************/
int rbl_svr_send_skt(int type,int skt_fd,int cnct_fd,char *buf,int size,struct sockaddr *addr);
int rbl_svr_send_skt(int type,int skt_fd,int cnct_fd,char *buf,int size,struct sockaddr *addr)
{
	int sen_len;
	sen_len = 0;
	if(type==1)
	{
		sen_len=rbl_tcp_svr_send_skt(skt_fd,cnct_fd,buf,size);
	}
	if(type==2)
	{
		sen_len=rbl_udp_svr_send_skt(skt_fd,buf,size,addr);
	}
   	return sen_len;
}

/**************************************************/
int rbl_svr_recv_skt(int type,int skt_fd,int cnct_fd,char *buf,int size,struct sockaddr *addr);
int rbl_svr_recv_skt(int type,int skt_fd,int cnct_fd,char *buf,int size,struct sockaddr *addr)
{
    int rec_len;
    rec_len = 0;
	if(type==1)
	{
		rec_len=rbl_tcp_svr_recv_skt(skt_fd,cnct_fd,buf,size);
	}
	if(type==2)
	{
		rec_len=rbl_udp_svr_recv_skt(skt_fd,buf,size,addr);
	}
   	return rec_len;
}

/**************************************************/
#include <fcntl.h>
void rbl_svr_set_nonblock(int type,int skt_fd);
void rbl_svr_set_nonblock(int type,int skt_fd)
{
	if(type==1)
	{
		rbl_tcp_svr_set_nonblock(skt_fd);
	}
	if(type==2)
	{
		rbl_udp_svr_set_nonblock(skt_fd);
	}
}

void rbl_svr_set_block(int type,int skt_fd);
void rbl_svr_set_block(int type,int skt_fd)
{
	if(type==1)
	{
		rbl_tcp_svr_set_block(skt_fd);
	}
	if(type==2)
	{
		rbl_udp_svr_set_block(skt_fd);
	}
}
/* end of svr.c */
