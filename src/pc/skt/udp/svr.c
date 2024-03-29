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

static  int    app_skt_fd, app_cnct_fd;
/**************************************************/
static void svr_create_skt(void);
static void svr_create_skt()
{
	app_skt_fd = -1;
    app_skt_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if( app_skt_fd != -1 )
    {
       	os_print("UDP Server create socket %d successfully\r\n",app_skt_fd);
    	return;
    }
   	os_print("UDP Server create socket error: %s(errno: %d)\n",strerror(errno),errno);
}
/**************************************************/
static struct sockaddr_in svraddr;
static void svr_bind_skt(void);
static void svr_bind_skt(void)
{
	if(app_skt_fd == -1)
		return;

    memset(&svraddr, 0, sizeof(svraddr));
    svraddr.sin_family = AF_INET;
    svraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    svraddr.sin_port = htons(APP_SKT_PORT);

    int ret;
    ret=bind(app_skt_fd, (struct sockaddr*)&svraddr, sizeof(svraddr));
    if( ret != -1)
    {
       	os_print("UDP Server Bind socket %d successfully for port %d\r\n",app_skt_fd,APP_SKT_PORT);
    	return;
    }

    os_print("UDP Server bind socket error: %s(errno: %d)\n",strerror(errno),errno);
    close(app_skt_fd);
    app_skt_fd=-1;
   	return;
}
/**************************************************/
static void svr_listen_skt(void);
static void svr_listen_skt(void)
{
}
/**************************************************/
static void svr_connect_skt(void);
static void svr_connect_skt(void)
{

}
/**************************************************/
static void svr_disconnect_skt(void);
static void svr_disconnect_skt(void)
{

}
/**************************************************/
static void svr_distroy_skt(void);
static void svr_distroy_skt(void)
{
	if(app_skt_fd == -1)
		return;

    close(app_skt_fd);
    app_skt_fd=-1;
}
/**************************************************/
void udp_svr_init_skt(void);
void udp_svr_init_skt()
{
    svr_create_skt();
    svr_bind_skt();
   	svr_listen_skt();
   	svr_connect_skt();
}
/**************************************************/
void udp_svr_free_skt(void);
void udp_svr_free_skt(void)
{
	svr_disconnect_skt();

	svr_distroy_skt();
}

/**************************************************/
extern void skt_log_packet(char *data, int size);
int udp_svr_recv_skt(char *buf,int size);
int udp_svr_recv_skt(char *buf,int size)
{
	if(app_skt_fd == -1)
		return 0;

	if(app_cnct_fd == -1)
		return 0;

	int rec_len;
	struct sockaddr addr;
	socklen_t length;
	length=sizeof(struct sockaddr);
	rec_len=recvfrom(app_cnct_fd,buf,size,0,(struct sockaddr*)&addr,&length);
	if(rec_len>0)
	{
		os_print("UDP Server Recv data %d bytes!\r\n",rec_len);
		skt_log_packet(buf, rec_len);
	}
   	return rec_len;
}
/**************************************************/
int udp_svr_send_skt(char *buf,int size);
int udp_svr_send_skt(char *buf,int size)
{
	if(app_skt_fd == -1)
		return 0;

	int sen_len;
	struct sockaddr addr;
	socklen_t length;
	length=sizeof(struct sockaddr);
	addr.sa_family=AF_INET;
	sen_len=sendto(app_cnct_fd, buf, size, 0,(struct sockaddr*)&addr,length);
	if(sen_len>0)
	{
		os_print("UDP Server Send data %d bytes!\r\n",sen_len);
		skt_log_packet(buf, sen_len);
	}
   	return sen_len;
}

/**************************************************/
#include <fcntl.h>
void udp_svr_set_nonblock(void);
void udp_svr_set_nonblock()
{
	int old,new;
	old=fcntl(app_skt_fd,F_GETFL,0);
	new = old|O_NONBLOCK;
	fcntl(app_skt_fd,F_SETFL,new);
}

void udp_svr_set_block(void);
void udp_svr_set_block()
{
	int old,new;
	old=fcntl(app_skt_fd,F_GETFL,0);
	new = old&(~O_NONBLOCK);
	fcntl(app_skt_fd,F_SETFL,new);
}
/* end of svr.c */
