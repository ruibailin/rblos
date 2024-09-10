/*---------------------------
 * clt.c
 *  Created on: Aug 8, 2017
 *      Author: Bailin Rui
 *---------------------------
 *
 *
 *
 *
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
//static int type;
/**************************************************/
int rbl_clt_init_skt(int type,char *ip,int port);
int rbl_clt_init_skt(int type,char *ip,int port)
{
	int fd;
	fd = -1;
	if(type==1)
	{
	    fd = rbl_tcp_clt_init_skt(ip,port);
	}
	if(type==2)
	{
	    fd = rbl_udp_clt_init_skt(ip,port);
	}
	return fd;
}
/**************************************************/
void rbl_clt_free_skt(int type,int skt_fd);
void rbl_clt_free_skt(int type,int skt_fd)
{
	if(type==1)
	{
		rbl_tcp_clt_free_skt(skt_fd);
	}
	if(type==2)
	{
		rbl_udp_clt_free_skt(skt_fd);
	}
}

/**************************************************/
int rbl_clt_send_skt(int type,int skt_fd,char *buf,int size);
int rbl_clt_send_skt(int type,int skt_fd,char *buf,int size)
{
	int sen_len;
	sen_len = 0;
	if(type==1)
	{
		sen_len=rbl_tcp_clt_send_skt(skt_fd,buf,size);
	}
	if(type==2)
	{
		sen_len=rbl_udp_clt_send_skt(skt_fd,buf,size);
	}
   	return sen_len;
}
/**************************************************/
int rbl_clt_recv_skt(int type,int skt_fd,char *buf,int size);
int rbl_clt_recv_skt(int type,int skt_fd,char *buf,int size)
{
    int rec_len;
    rec_len = 0;
	if(type==1)
	{
		rec_len=rbl_tcp_clt_recv_skt(skt_fd,buf,size);
	}
	if(type==2)
	{
		rec_len=rbl_udp_clt_recv_skt(skt_fd,buf,size);
	}
   	return rec_len;
}


/**************************************************/
#include <fcntl.h>
void rbl_clt_set_nonblock(int type,int skt_fd);
void rbl_clt_set_nonblock(int type,int skt_fd)
{
	if(type==1)
	{
		rbl_tcp_clt_set_nonblock(skt_fd);
	}
	if(type==2)
	{
		rbl_udp_clt_set_nonblock(skt_fd);
	}
}

void rbl_clt_set_block(int type,int skt_fd);
void rbl_clt_set_block(int type,int skt_fd)
{
	if(type==1)
	{
		rbl_tcp_clt_set_block(skt_fd);
	}
	if(type==2)
	{
		rbl_udp_clt_set_block(skt_fd);
	}
}
/* end of clt.c */
