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
static int clt_udp_skt_fd;
static void clt_create_skt(void);
static void clt_create_skt()
{
	clt_udp_skt_fd = -1;
	    clt_udp_skt_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(clt_udp_skt_fd>=0)
    {
    	os_print("UDP Client create socket successfully %d\r\n", clt_udp_skt_fd);
    	return;
    }
	os_print("UDP Client create socket error: %s(errno: %d)\n", strerror(errno),errno);
}
/**************************************************/
static struct sockaddr_in svr_skt_addr;
static socklen_t svr_skt_len;
//static const char *svr_ip_addr="192.168.1.1";
static char *svr_ip_addr="10.0.5.110";
//static char *svr_ip_addr="127.0.0.1";
static void clt_bind_skt(void);
static void clt_bind_skt(void)
{
    if( clt_udp_skt_fd < 0)
    	return;

    memset(&svr_skt_addr, 0, sizeof(svr_skt_addr));
    svr_skt_addr.sin_family = AF_INET;
    svr_skt_addr.sin_port = htons(APP_SKT_PORT);
    svr_skt_len=sizeof(struct sockaddr_in);

    int ret;
    ret=inet_pton(AF_INET, svr_ip_addr, &svr_skt_addr.sin_addr);
 //   svr_skt_addr.sin_addr=inet_addr(svr_ip_addr);

    if( ret != -1)
    {
       	os_print("UDP Client Bind socket %d successfully for port %d\r\n",clt_udp_skt_fd,APP_SKT_PORT);
    	return;
    }

    os_print("UDP Client bind socket error: %s(errno: %d)\n",strerror(errno),errno);
    close(clt_udp_skt_fd);
    clt_udp_skt_fd=-1;
}
/**************************************************/
static void clt_connect_skt(void);
static void clt_connect_skt(void)
{
	int ret;
    ret = connect(clt_udp_skt_fd, (struct sockaddr*)&svr_skt_addr, sizeof(svr_skt_addr));
    if( ret >= 0)
    {
       	os_print("UDP Client connect %d successfully to IP %s\n",clt_udp_skt_fd,svr_ip_addr);
       	return;
    }
   	os_print("UDP Client connect error: %s(errno: %d)\n",strerror(errno),errno);
   	close(clt_udp_skt_fd);
   	clt_udp_skt_fd=-1;
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
   	os_print("UDP Client disconnect socket %d\n",clt_udp_skt_fd);
   	close(clt_udp_skt_fd);
   	clt_udp_skt_fd=-1;
}
/**************************************************/
void udp_clt_init_skt(int type);
void udp_clt_init_skt(int type)
{
    clt_create_skt();
    clt_bind_skt();

	clt_connect_skt();
}
/**************************************************/
void udp_clt_free_skt(void);
void udp_clt_free_skt(void)
{
	clt_disconnect_skt();

	clt_distroy_skt();
}

extern void skt_log_packet(char *data, int size);
/**************************************************/
int udp_clt_send_skt(char *buf,int size);
int udp_clt_send_skt(char *buf,int size)
{
	if(clt_udp_skt_fd < 0)
		return 0;

	int sen_len;
	sen_len = sendto(clt_udp_skt_fd, buf, size, 0,0x0L,sizeof(struct sockaddr));
	if(sen_len>0)
	{
		os_print("UDP Client Send data %d bytes!\r\n",sen_len);
		skt_log_packet(buf, sen_len);
	}
   	return sen_len;
}
/**************************************************/
int udp_clt_recv_skt(char *buf,int size);
int udp_clt_recv_skt(char *buf,int size)
{
    int rec_len;

	if(clt_udp_skt_fd < 0)
		return 0;
	struct sockaddr addr;
	socklen_t length;
    rec_len = recvfrom(clt_udp_skt_fd, buf, size,0,&addr,&length);
	if(rec_len>0)
	{
		os_print("UDP Client Recv data %d bytes!\r\n",rec_len);
		skt_log_packet(buf, rec_len);
	}
   	return rec_len;
}

/**************************************************/
int udp_clt_init_add(char *ip_addr);
int udp_clt_init_add(char *ip_addr)
{
    int i;
    int ip[4];
    for(i=0;i<4;i++)
    	ip[i]=256;
    sscanf((const char *)ip_addr, "%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);
    for(i=0;i<4;i++)
    {
        if(ip[i]>255)
        	return -1;
        if(ip[i]<0)
        	return -1;
    }

    sprintf(svr_ip_addr,"%d.%d.%d.%d",ip[0], ip[1], ip[2], ip[3]);
    os_print("input IP address:%s\r\n",svr_ip_addr);
    return 1;
}
/**************************************************/
#include <fcntl.h>
void udp_clt_set_nonblock(void);
void udp_clt_set_nonblock()
{
	int old,new;
	old=fcntl(clt_udp_skt_fd,F_GETFL,0);
	new = old|O_NONBLOCK;
	fcntl(clt_udp_skt_fd,F_SETFL,new);
}

void udp_clt_set_block(void);
void udp_clt_set_block()
{
	int old,new;
	old=fcntl(clt_udp_skt_fd,F_GETFL,0);
	new = old&(~O_NONBLOCK);
	fcntl(clt_udp_skt_fd,F_SETFL,new);
}
/* end of clt.c */
