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
static int clt_tcp_skt_fd;
static void clt_create_skt(void);
static void clt_create_skt()
{
	clt_tcp_skt_fd = -1;
	clt_tcp_skt_fd = socket(AF_INET, SOCK_STREAM, 0);
    if( clt_tcp_skt_fd != -1 )
    {
       	os_print("TCP Client create socket %d successfully\r\n",clt_tcp_skt_fd);
    	return;
    }
   	os_print("TCP Client create socket error: %s(errno: %d)\n",strerror(errno),errno);
}
/**************************************************/
static struct sockaddr_in svr_skt_addr;
static const char *svr_ip_addr="192.168.1.1";
//static char *svr_ip_addr="10.0.5.90";
//static char *svr_ip_addr="127.0.0.1";
static void clt_bind_skt(void);
static void clt_bind_skt(void)
{
    if( clt_tcp_skt_fd < 0)
    	return;

    memset(&svr_skt_addr, 0, sizeof(svr_skt_addr));
    svr_skt_addr.sin_family = AF_INET;
    svr_skt_addr.sin_port = htons(APP_SKT_PORT);

    int ret;
    ret=inet_pton(AF_INET, svr_ip_addr, &svr_skt_addr.sin_addr);
    if( ret != -1)
    {
       	os_print("TCP Client Bind socket %d successfully for port %d\r\n",clt_tcp_skt_fd,APP_SKT_PORT);
    	return;
    }

    os_print("TCP Client bind socket error: %s(errno: %d)\n",strerror(errno),errno);
    close(clt_tcp_skt_fd);
    clt_tcp_skt_fd=-1;
}
/**************************************************/
static void clt_connect_skt(void);
static void clt_connect_skt(void)
{
	int ret;
    ret = connect(clt_tcp_skt_fd, (struct sockaddr*)&svr_skt_addr, sizeof(svr_skt_addr));
    if( ret >= 0)
    {
    	os_print("TCP Client connect socket %d\r\n to IP\r\n",clt_tcp_skt_fd);
    	return;
    }

   	os_print("TCP Client connect socket error: %s(errno: %d)",strerror(errno),errno);
   	close(clt_tcp_skt_fd);
   	clt_tcp_skt_fd=-1;
}
/**************************************************/
static void clt_disconnect_skt(void);
static void clt_disconnect_skt(void)
{
	os_print("TCP Client connect %d successfully released!\n",clt_tcp_skt_fd);
}
/**************************************************/
static void clt_distroy_skt(void);
static void clt_distroy_skt(void)
{
	if(clt_tcp_skt_fd<0)
		return;
   	close(clt_tcp_skt_fd);
	os_print("TCP Client connect %d successfully destroyed!\n",clt_tcp_skt_fd);
   	clt_tcp_skt_fd=-1;
}
/**************************************************/
void tcp_clt_init_skt(void);
void tcp_clt_init_skt()
{
    clt_create_skt();
    clt_bind_skt();

	clt_connect_skt();
}
/**************************************************/
void tcp_clt_free_skt(void);
void tcp_clt_free_skt(void)
{
	clt_disconnect_skt();

	clt_distroy_skt();
}

extern void skt_log_packet(char *data, int size);
/**************************************************/
int tcp_clt_send_skt(char *buf,int size);
int tcp_clt_send_skt(char *buf,int size)
{
	if(clt_tcp_skt_fd < 0)
		return 0;

	int sen_len;
	sen_len = send(clt_tcp_skt_fd, buf, size, 0);
	if(sen_len>0)
	{
		os_print("TCP Client Send data %d bytes!\r\n",sen_len);
		skt_log_packet(buf, sen_len);
	}
   	return sen_len;
}
/**************************************************/
int tcp_clt_recv_skt(char *buf,int size);
int tcp_clt_recv_skt(char *buf,int size)
{
    int rec_len;

	if(clt_tcp_skt_fd < 0)
		return 0;
    rec_len = recv(clt_tcp_skt_fd, buf, size,0);
	if(rec_len>0)
	{
		os_print("TCP Client Recv data %d bytes!\r\n",rec_len);
		skt_log_packet(buf, rec_len);
	}
   	return rec_len;
}

/**************************************************/
int tcp_clt_init_add(char *ip_addr);
int tcp_clt_init_add(char *ip_addr)
{
    int i;
    int ip[4];
    for(i=0;i<4;i++)
    	ip[i]=256;
    sscanf((const char *)ip_addr, "%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);
    for(i=0;i<4;i++)
    {
        if(ip[i]>255)
        	return 0;
        if(ip[i]<0)
        	return 0;
    }

    sprintf(svr_ip_addr,"%d.%d.%d.%d",ip[0], ip[1], ip[2], ip[3]);
    os_print("input IP address:%s\r\n",svr_ip_addr);
    return 1;
}
/**************************************************/
#include <fcntl.h>
void tcp_clt_set_nonblock(void);
void tcp_clt_set_nonblock()
{
	int old,new;
	old=fcntl(clt_tcp_skt_fd,F_GETFL,0);
	new = old|O_NONBLOCK;
	fcntl(clt_tcp_skt_fd,F_SETFL,new);
}

void tcp_clt_set_block(void);
void tcp_clt_set_block()
{
	int old,new;
	old=fcntl(clt_tcp_skt_fd,F_GETFL,0);
	new = old&(~O_NONBLOCK);
	fcntl(clt_tcp_skt_fd,F_SETFL,new);
}
/* end of clt.c */
