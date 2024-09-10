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

//static  int    skt_fd, cnct_fd;
/**************************************************/
static int svr_create_skt(void);
static int svr_create_skt()
{
	int skt_fd;
	skt_fd = -1;
    skt_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if( skt_fd != -1 )
    {
       	rbl_print("UDP Server create socket %d successfully\r\n",skt_fd);
    }
    else
    {
    	rbl_print("UDP Server create socket error: %s(errno: %d)\n",strerror(errno),errno);
    }
	return skt_fd;
}
/**************************************************/
//static struct sockaddr_in svraddr;
static int svr_bind_skt(int skt_fd,int port);
static int svr_bind_skt(int skt_fd,int port)
{
	if(skt_fd < 0)
		return -1;

	struct sockaddr_in svraddr;
    memset(&svraddr, 0, sizeof(svraddr));
    svraddr.sin_family = AF_INET;
    svraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    svraddr.sin_port = htons(port);

    int ret;
    ret=bind(skt_fd, (struct sockaddr*)&svraddr, sizeof(svraddr));
    if( ret != -1)
    {
       	rbl_print("UDP Server Bind socket %d successfully for port %d\r\n",skt_fd,port);
    	return 0;
    }

    rbl_print("UDP Server bind socket error: %s(errno: %d)\n",strerror(errno),errno);
    close(skt_fd);
   	return -1;
}
/**************************************************/
static int svr_listen_skt(int skt_fd);
static int svr_listen_skt(int skt_fd)
{
	return 0;
}
/**************************************************/
static int svr_connect_skt(int skt_fd);
static int svr_connect_skt(int skt_fd)
{
	return 1;
}
/**************************************************/
static void svr_disconnect_skt(int skt_fd);
static void svr_disconnect_skt(int skt_fd)
{

}
/**************************************************/
static void svr_distroy_skt(int skt_fd);
static void svr_distroy_skt(int skt_fd)
{
	if(skt_fd <0)
		return;

    close(skt_fd);
}
/**************************************************/
int rbl_udp_svr_init_skt(int port);
int rbl_udp_svr_init_skt(int port)
{
	int skt_fd;
	skt_fd = svr_create_skt();
	if(skt_fd < 0)
		return -1;
	int ret;
    ret = svr_bind_skt(skt_fd,port);
    if(ret < 0)
    	return ret;
   	svr_listen_skt(skt_fd);
   	return skt_fd;
}

int rbl_udp_svr_conn_skt(int skt_fd);	//compatible with tcp
int rbl_udp_svr_conn_skt(int skt_fd)
{
   	svr_connect_skt(skt_fd);
   	return 1;
}
/**************************************************/
void rbl_udp_svr_free_skt(int skt_fd,int cnct_fd);
void rbl_udp_svr_free_skt(int skt_fd,int cnct_fd)
{
	svr_disconnect_skt(skt_fd);

	svr_distroy_skt(skt_fd);
}

/**************************************************/
extern void rbl_log_packet(char *data, int size);
int rbl_udp_svr_recv_skt(int skt_fd,char *buf,int size,struct sockaddr *addr);
int rbl_udp_svr_recv_skt(int skt_fd,char *buf,int size,struct sockaddr *addr)
{
	if(skt_fd == -1)
		return 0;

	int rec_len;
	socklen_t length;
	length=sizeof(struct sockaddr);
	rec_len=recvfrom(skt_fd,buf,size,0,(struct sockaddr*)addr,&length);
	if(rec_len>0)
	{
		char ip_addr[16];
		unsigned int port;
		port = addr->sa_data[0];
		port <<= 8;
		port += addr->sa_data[1];
		port &= 0xFFFF;
		sprintf(ip_addr,"%d.%d.%d.%d",addr->sa_data[2],addr->sa_data[3],addr->sa_data[4],addr->sa_data[5]);
		rbl_print("UDP Server Recv data %d bytes from ip:%s,port :%d\r\n",rec_len,ip_addr,(int)port);
		rbl_log_packet(buf, rec_len);
	}
   	return rec_len;
}
/**************************************************/
int rbl_udp_svr_send_skt(int skt_fd,char *buf,int size,struct sockaddr *addr);
int rbl_udp_svr_send_skt(int skt_fd,char *buf,int size,struct sockaddr *addr)
{
	if(skt_fd == -1)
		return 0;

	int sen_len;
	socklen_t length;
	length=sizeof(struct sockaddr);
	sen_len=sendto(skt_fd, buf, size, 0,(struct sockaddr*)addr,length);
	if(sen_len>0)
	{
		char ip_addr[16];
		unsigned int port;
		port = addr->sa_data[0];
		port <<= 8;
		port += addr->sa_data[1];
		port &= 0xFFFF;
		sprintf(ip_addr,"%d.%d.%d.%d",addr->sa_data[2],addr->sa_data[3],addr->sa_data[4],addr->sa_data[5]);
		rbl_print("UDP Server Send data %d bytes to ip:%s,port:%d\r\n",sen_len,ip_addr,(int)port);
		rbl_log_packet(buf, sen_len);
	}
   	return sen_len;
}

/**************************************************/
#include <fcntl.h>
void rbl_udp_svr_set_nonblock(int skt_fd);
void rbl_udp_svr_set_nonblock(int skt_fd)
{
	int old,new;
	old=fcntl(skt_fd,F_GETFL,0);
	new = old|O_NONBLOCK;
	fcntl(skt_fd,F_SETFL,new);
}

void rbl_udp_svr_set_block(int skt_fd);
void rbl_udp_svr_set_block(int skt_fd)
{
	int old,new;
	old=fcntl(skt_fd,F_GETFL,0);
	new = old&(~O_NONBLOCK);
	fcntl(skt_fd,F_SETFL,new);
}
/* end of svr.c */
