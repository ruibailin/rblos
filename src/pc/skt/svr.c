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


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "1imp.h"

/**************************************************/

static  int    app_skt_fd, app_cnct_fd;

/**************************************************/
static void svr_create_skt(int type);
static void svr_create_skt(int type)
{
	app_skt_fd = -1;
	if(type==1)		//TCP
		app_skt_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(type==2)		//UDP
	    app_skt_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if( app_skt_fd != -1 )
    	return;
   	os_print("create socket error: %s(errno: %d)\n",strerror(errno),errno);
}
/**************************************************/
static void svr_bind_skt(void);
static void svr_bind_skt(void)
{
	if(app_skt_fd == -1)
		return;

	struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(APP_SKT_PORT);

    int ret;
    ret=bind(app_skt_fd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if( ret != -1)
    	return;

    os_print("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
    close(app_skt_fd);
    app_skt_fd=-1;
   	return;
}
/**************************************************/
static void svr_listen_skt(void);
static void svr_listen_skt(void)
{
	if(app_skt_fd == -1)
		return;

    int ret;
    ret=listen(app_skt_fd, 10);
    if( ret != -1)
    	return;

    os_print("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
    close(app_skt_fd);
    app_skt_fd=-1;
}
/**************************************************/
static void svr_connect_skt(void);
static void svr_connect_skt(void)
{
	if(app_skt_fd == -1)
		return;

	os_print("======waiting for client's request======\n");
    app_cnct_fd = accept(app_skt_fd, (struct sockaddr*)NULL, NULL);
    if( app_cnct_fd != -1)
    	return;

   	os_print("Server accept socket error: %s(errno: %d)",strerror(errno),errno);
    close(app_skt_fd);
    app_skt_fd=-1;
}
/**************************************************/
static void svr_disconnect_skt(void);
static void svr_disconnect_skt(void)
{
	if(app_skt_fd == -1)
		return;

	os_print("Server connect %d successfully released!\n",app_cnct_fd);
	close(app_cnct_fd);
	app_cnct_fd=-1;
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
void app_svr_init_skt(int type);
void app_svr_init_skt(int type)
{
    svr_create_skt(type);
    svr_bind_skt();
    svr_listen_skt();

	svr_connect_skt();
}
/**************************************************/
void app_svr_free_skt(void);
void app_svr_free_skt(void)
{
	svr_disconnect_skt();

	svr_distroy_skt();
}

/**************************************************/
int app_svr_recv_skt(char *buf,int size);
int app_svr_recv_skt(char *buf,int size)
{
	if(app_skt_fd == -1)
		return 0;

	if(app_cnct_fd == -1)
		return 0;

	int rec_len;
	rec_len = recv(app_cnct_fd, buf, size, 0);
   	return rec_len;
}
/**************************************************/
int app_svr_send_skt(char *buf,int size);
int app_svr_send_skt(char *buf,int size)
{
	if(app_skt_fd == -1)
		return 0;

	if(app_cnct_fd == -1)
		return 0;

	int sen_len;
	sen_len=send(app_cnct_fd, buf, size, 0);
   	return sen_len;
}

/* end of svr.c */
