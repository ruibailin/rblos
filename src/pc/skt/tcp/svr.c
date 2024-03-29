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

static int tcp_svr_skt_fd, tcp_svr_cnct_fd;
/**************************************************/
static void svr_create_skt(void);
static void svr_create_skt()
{
	tcp_svr_skt_fd = -1;
	tcp_svr_skt_fd = socket(AF_INET, SOCK_STREAM, 0);
    if( tcp_svr_skt_fd != -1 )
    {
       	os_print("TCP Server create socket %d successfully\r\n",tcp_svr_skt_fd);
    	return;
    }
   	os_print("TCP Server create socket error: %s(errno: %d)\n",strerror(errno),errno);
}
/**************************************************/
static struct sockaddr_in svraddr;
static socklen_t svrlen;
static void svr_bind_skt(void);
static void svr_bind_skt(void)
{
	if(tcp_svr_skt_fd == -1)
		return;

    memset(&svraddr, 0, sizeof(svraddr));
    svraddr.sin_family = AF_INET;
    svraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    svraddr.sin_port = htons(APP_SKT_PORT);
    svrlen=sizeof(struct sockaddr_in);

    int ret;
    ret=bind(tcp_svr_skt_fd, (struct sockaddr*)&svraddr, sizeof(svraddr));
    if( ret != -1)
    {
       	os_print("TCP Server Bind socket %d successfully for port %d\r\n",tcp_svr_skt_fd,APP_SKT_PORT);
    	return;
    }

    os_print("TCP Server bind socket error: %s(errno: %d)\n",strerror(errno),errno);
    close(tcp_svr_skt_fd);
    tcp_svr_skt_fd=-1;
   	return;
}
/**************************************************/
static void svr_listen_skt(void);
static void svr_listen_skt(void)
{
	if(tcp_svr_skt_fd == -1)
		return;

    int ret;
    os_print("TCP Server is listening socket %d on port %d\r\n",tcp_svr_skt_fd,APP_SKT_PORT);
    ret=listen(tcp_svr_skt_fd, 2);
    if( ret != -1)
    {
        os_print("TCP Server socket %d is connected!\r\n",tcp_svr_skt_fd);
    	return;
    }

    os_print("TCP Server listen socket %d error: %s(errno: %d)\n",tcp_svr_skt_fd,strerror(errno),errno);
    close(tcp_svr_skt_fd);
    tcp_svr_skt_fd=-1;
}
/**************************************************/
static void svr_connect_skt(void);
static void svr_connect_skt(void)
{
	if(tcp_svr_skt_fd == -1)
		return;

    tcp_svr_cnct_fd = accept(tcp_svr_skt_fd, (struct sockaddr*)NULL, NULL);
    if( tcp_svr_cnct_fd != -1)
    {
    	os_print("TCP Server accept new socket %d\r\n",tcp_svr_cnct_fd);
    	return;
    }

   	os_print("TCP Server accept socket error: %s(errno: %d)",strerror(errno),errno);
    close(tcp_svr_skt_fd);
    tcp_svr_skt_fd=-1;
}
/**************************************************/
static void svr_disconnect_skt(void);
static void svr_disconnect_skt(void)
{
	if(tcp_svr_skt_fd == -1)
		return;

	os_print("TCP Server connect %d successfully released!\n",tcp_svr_cnct_fd);
	close(tcp_svr_cnct_fd);
	tcp_svr_cnct_fd=-1;
}
/**************************************************/
static void svr_distroy_skt(void);
static void svr_distroy_skt(void)
{
	if(tcp_svr_skt_fd == -1)
		return;
	os_print("TCP Server connect %d successfully destroyed!\n",tcp_svr_skt_fd);
    close(tcp_svr_skt_fd);
    tcp_svr_skt_fd=-1;
}
/**************************************************/
void tcp_svr_init_skt(int type);
void tcp_svr_init_skt(int type)
{
    svr_create_skt();
    svr_bind_skt();
   	svr_listen_skt();
   	svr_connect_skt();
}
/**************************************************/
void tcp_svr_free_skt(void);
void tcp_svr_free_skt(void)
{
	svr_disconnect_skt();

	svr_distroy_skt();
}

/**************************************************/
extern void skt_log_packet(char *data, int size);
int tcp_svr_recv_skt(char *buf,int size);
int tcp_svr_recv_skt(char *buf,int size)
{
	if(tcp_svr_skt_fd == -1)
		return 0;

	if(tcp_svr_cnct_fd == -1)
		return 0;

	int rec_len;
	rec_len = recv(tcp_svr_cnct_fd, buf, size, 0);
	if(rec_len>0)
	{
		os_print("TCP Server Recv data %d bytes!\r\n",rec_len);
		skt_log_packet(buf, rec_len);
	}
   	return rec_len;
}
/**************************************************/
int tcp_svr_send_skt(char *buf,int size);
int tcp_svr_send_skt(char *buf,int size)
{
	if(tcp_svr_skt_fd == -1)
		return 0;

	if(tcp_svr_cnct_fd == -1)
		return 0;

	int sen_len;
	sen_len=send(tcp_svr_cnct_fd, buf, size, 0);
	if(sen_len>0)
	{
		os_print("TCP Server Send data %d bytes!\r\n",sen_len);
		skt_log_packet(buf, sen_len);
	}
   	return sen_len;
}

/**************************************************/
#include <fcntl.h>
void tcp_svr_set_nonblock(void);
void tcp_svr_set_nonblock()
{
	int old,new;
	old=fcntl(tcp_svr_skt_fd,F_GETFL,0);
	new = old|O_NONBLOCK;
	fcntl(tcp_svr_skt_fd,F_SETFL,new);
}

void tcp_svr_set_block(void);
void tcp_svr_set_block()
{
	int old,new;
	old=fcntl(tcp_svr_skt_fd,F_GETFL,0);
	new = old&(~O_NONBLOCK);
	fcntl(tcp_svr_skt_fd,F_SETFL,new);
}
/* end of svr.c */
