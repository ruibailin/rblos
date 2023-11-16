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


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>

#include "1imp.h"
#define os_print(x...)  	printf(x);
/**************************************************/
static int app_skt_fd;
static void clt_create_skt(void);
static void clt_create_skt(void)
{
    app_skt_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(app_skt_fd>=0)
    	return;
	os_print("Client create socket error: %s(errno: %d)\n", strerror(errno),errno);
}
/**************************************************/
static struct sockaddr_in svr_skt_addr;
static const char *svr_ip_addr="192.168.137.200";
static void clt_bind_skt(void);
static void clt_bind_skt(void)
{
    if( app_skt_fd < 0)
    	return;

    memset(&svr_skt_addr, 0, sizeof(svr_skt_addr));
    svr_skt_addr.sin_family = AF_INET;
    svr_skt_addr.sin_port = htons(APP_SKT_PORT);

    int ret;
    ret=inet_pton(AF_INET, svr_ip_addr, &svr_skt_addr.sin_addr);
    if( ret >0 )
    	return;

    os_print("inet_pton error for %s\n",svr_ip_addr);
    close(app_skt_fd);
    app_skt_fd=-1;
}
/**************************************************/
static void clt_connect_skt(void);
static void clt_connect_skt(void)
{
	int ret;
    ret = connect(app_skt_fd, (struct sockaddr*)&svr_skt_addr, sizeof(svr_skt_addr));
    if( ret >= 0)
    	return;

   	os_print("Client connect error: %s(errno: %d)\n",strerror(errno),errno);
   	close(app_skt_fd);
   	app_skt_fd=-1;
}
/**************************************************/
static void clt_disconnect_skt(void);
static void clt_disconnect_skt(void)
{

}
/**************************************************/
static void clt_distroy_skt(void);
static void clt_distroy_skt(void)
{
   	os_print("Client disconnect socket %d\n",app_skt_fd);
   	close(app_skt_fd);
   	app_skt_fd=-1;
}
/**************************************************/
void app_clt_init_skt(void);
void app_clt_init_skt(void)
{
    clt_create_skt();
    clt_bind_skt();

	clt_connect_skt();
}
/**************************************************/
void app_clt_free_skt(void);
void app_clt_free_skt(void)
{
	clt_disconnect_skt();

	clt_distroy_skt();
}


/**************************************************/
int app_clt_send_skt(char *buf,int size);
int app_clt_send_skt(char *buf,int size)
{
	if(app_skt_fd < 0)
		return 0;

	int sen_len;
    sen_len = send(app_skt_fd, buf, size, 0);
   	return sen_len;
}
/**************************************************/
int app_clt_recv_skt(char *buf,int size);
int app_clt_recv_skt(char *buf,int size)
{
    int rec_len;

	if(app_skt_fd < 0)
		return 0;
    rec_len = recv(app_skt_fd, buf, size,0);
   	return rec_len;
}

/* end of clt.c */
