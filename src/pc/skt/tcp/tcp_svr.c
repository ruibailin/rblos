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

//static int skt_fd, cnct_fd;
/**************************************************/
static int svr_create_skt(void);
static int svr_create_skt()
{
	int skt_fd;
	skt_fd = -1;
	skt_fd = socket(AF_INET, SOCK_STREAM, 0);
    if( skt_fd != -1 )
    {
       	rbl_print("TCP Server create socket %d successfully\r\n",skt_fd);
    }
    else
    {
       	rbl_print("TCP Server create socket error: %s(errno: %d)\n",strerror(errno),errno);
    }
    return skt_fd;
}
/**************************************************/
//static struct sockaddr_in svraddr;
//static socklen_t svrlen;
static int svr_bind_skt(int skt_fd,int port);
static int svr_bind_skt(int skt_fd,int port)
{
	if(skt_fd == -1)
		return -1;
	struct sockaddr_in svraddr;
    memset(&svraddr, 0, sizeof(svraddr));
    svraddr.sin_family = AF_INET;
    svraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    svraddr.sin_port = htons(port);
    socklen_t svrlen;
    svrlen=sizeof(struct sockaddr_in);

    int ret;
    ret=bind(skt_fd, (struct sockaddr*)&svraddr, sizeof(svraddr));
    if( ret != -1)
    {
       	rbl_print("TCP Server Bind socket %d successfully for port %d\r\n",skt_fd,port);
    	return 0;
    }

    rbl_print("TCP Server bind socket error: %s(errno: %d)\n",strerror(errno),errno);
    close(skt_fd);
   	return -1;
}
/**************************************************/
#define MAX_TCP_CONNECTION	8
static int svr_listen_skt(int skt_fd,int port);
static int svr_listen_skt(int skt_fd,int port)
{
	if(skt_fd == -1)
		return -1;

    int ret;
    rbl_print("TCP Server is listening socket %d on port %d\r\n",skt_fd,port);
    ret=listen(skt_fd, MAX_TCP_CONNECTION);
    if( ret != -1)
    {
        rbl_print("TCP Server socket %d is connected!\r\n",skt_fd);
    	return 0;
    }

    rbl_print("TCP Server listen socket %d error: %s(errno: %d)\n",skt_fd,strerror(errno),errno);
    close(skt_fd);
	return -1;
}
/**************************************************/
static int svr_connect_skt(int skt_fd,void *clt_info);
static int svr_connect_skt(int skt_fd,void *clt_info)
{
	if(skt_fd == -1)
		return -1;

	struct sockaddr *addr;
	addr = (struct sockaddr *)clt_info;
	int cnct_fd;
	socklen_t length;
	length=sizeof(struct sockaddr);
    cnct_fd = accept(skt_fd, (struct sockaddr*)addr, &length);
    if( cnct_fd != -1)
    {
		char ip_addr[16];
		unsigned int port;
		port = addr->sa_data[0];
		port <<= 8;
		port += addr->sa_data[1];
		port &= 0xFFFF;
		sprintf(ip_addr,"%d.%d.%d.%d",addr->sa_data[2],addr->sa_data[3],addr->sa_data[4],addr->sa_data[5]);
    	rbl_print("TCP Server accept new socket %d from IP %s,port %d\r\n",cnct_fd,ip_addr,port);
    	return cnct_fd;
    }
    if(errno == 11)
    	return -1;

   	rbl_print("TCP Server accept socket error: %s(errno: %d)",strerror(errno),errno);
    close(skt_fd);
	return -1;
}
/**************************************************/
static void svr_disconnect_skt(int skt_fd,int cnct_fd);
static void svr_disconnect_skt(int skt_fd,int cnct_fd)
{
	if(skt_fd == -1)
		return;

	rbl_print("TCP Server connect %d successfully released!\n",cnct_fd);
	close(cnct_fd);
}
/**************************************************/
static void svr_distroy_skt(int skt_fd,int cnct_fd);
static void svr_distroy_skt(int skt_fd,int cnct_fd)
{
	if(skt_fd == -1)
		return;
	rbl_print("TCP Server connect %d successfully destroyed!\n",skt_fd);
    close(skt_fd);
}
/**************************************************/
int rbl_tcp_svr_init_skt(int port);
int rbl_tcp_svr_init_skt(int port)
{
	int skt_fd;
	int ret;
    skt_fd = svr_create_skt();
    ret = svr_bind_skt(skt_fd,port);
    if(ret < 0)
    	return ret;
   	ret = svr_listen_skt(skt_fd,port);
    if(ret < 0)
    	return ret;
   	return skt_fd;
}

int rbl_tcp_svr_conn_skt(int skt_fd,void *clt_info);
int rbl_tcp_svr_conn_skt(int skt_fd,void *clt_info)
{
	int cnct_fd;
	struct sockaddr *addr;
	addr = (struct sockaddr *)clt_info;
   	cnct_fd = svr_connect_skt(skt_fd,addr);
   	return cnct_fd;
}
/**************************************************/
void rbl_tcp_svr_free_skt(int skt_fd,int cnct_fd);
void rbl_tcp_svr_free_skt(int skt_fd,int cnct_fd)
{
	svr_disconnect_skt(skt_fd,cnct_fd);

	svr_distroy_skt(skt_fd,cnct_fd);
}

/**************************************************/
extern void rbl_log_packet(char *data, int size);
int rbl_tcp_svr_recv_skt(int skt_fd,int cnct_fd,char *buf,int size);
int rbl_tcp_svr_recv_skt(int skt_fd,int cnct_fd,char *buf,int size)
{
	if(skt_fd == -1)
		return 0;

	if(cnct_fd == -1)
		return 0;

	int rec_len;
	rec_len = recv(cnct_fd, buf, size, 0);
	if(rec_len>0)
	{
		rbl_print("TCP Server Recv data %d bytes!\r\n",rec_len);
		rbl_log_packet(buf, rec_len);
	}
   	return rec_len;
}
/**************************************************/
int rbl_tcp_svr_send_skt(int skt_fd,int cnct_fd,char *buf,int size);
int rbl_tcp_svr_send_skt(int skt_fd,int cnct_fd,char *buf,int size)
{
	if(skt_fd == -1)
		return 0;

	if(cnct_fd == -1)
		return 0;

	int sen_len;
	sen_len=send(cnct_fd, buf, size, 0);
	if(sen_len>0)
	{
		rbl_print("TCP Server Send data %d bytes!\r\n",sen_len);
		rbl_log_packet(buf, sen_len);
	}
   	return sen_len;
}

/**************************************************/
#include <fcntl.h>
void rbl_tcp_svr_set_nonblock(int skt_fd);
void rbl_tcp_svr_set_nonblock(int skt_fd)
{
	int old,new;
	old=fcntl(skt_fd,F_GETFL,0);
	new = old|O_NONBLOCK;
	fcntl(skt_fd,F_SETFL,new);
}

void rbl_tcp_svr_set_block(int skt_fd);
void rbl_tcp_svr_set_block(int skt_fd)
{
	int old,new;
	old=fcntl(skt_fd,F_GETFL,0);
	new = old&(~O_NONBLOCK);
	fcntl(skt_fd,F_SETFL,new);
}
/* end of svr.c */
