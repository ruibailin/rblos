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
static int clt_create_skt(void);
static int clt_create_skt()
{
	int skt_fd;
	skt_fd = -1;
	    skt_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(skt_fd>=0)
    {
    	rbl_print("UDP Client create socket successfully %d\r\n", skt_fd);
    	return skt_fd;
    }
	rbl_print("UDP Client create socket error: %s(errno: %d)\n", strerror(errno),errno);
	return -1;
}
/**************************************************/
//static struct sockaddr_in svr_skt_addr;
//static socklen_t svr_skt_len;
//static const char *svr_ip="192.168.1.1";
//static char *svr_ip="10.0.5.110";
//static char *svr_ip="127.0.0.1";
static int clt_bind_skt(int skt_fd,char *svr_ip,int port);
static int clt_bind_skt(int skt_fd,char *svr_ip,int port)
{
    if( skt_fd < 0)
    	return -1;
    return 0;

    struct sockaddr_in svr_skt_addr;
    socklen_t svr_skt_len;
    memset(&svr_skt_addr, 0, sizeof(svr_skt_addr));
    svr_skt_addr.sin_family = AF_INET;
    svr_skt_addr.sin_port = htons(port);
    svr_skt_len=sizeof(struct sockaddr_in);

    int ret;
    ret=inet_pton(AF_INET, svr_ip, &svr_skt_addr.sin_addr);
 //   svr_skt_addr.sin_addr=inet_addr(svr_ip);

    if( ret != -1)
    {
       	rbl_print("UDP Client Bind socket %d successfully for port %d\r\n",skt_fd,port);
    	return 0;
    }

    rbl_print("UDP Client bind socket error: %s(errno: %d)\n",strerror(errno),errno);
    close(skt_fd);
    return -1;
}
/**************************************************/
static int clt_connect_skt(int skt_fd,char *svr_ip,int port);
static int clt_connect_skt(int skt_fd,char *svr_ip,int port)
{
    if( skt_fd < 0)
    	return -1;
    struct sockaddr_in svr_skt_addr;
    socklen_t svr_skt_len;
    memset(&svr_skt_addr, 0, sizeof(svr_skt_addr));
    svr_skt_addr.sin_family = AF_INET;
    svr_skt_addr.sin_port = htons(port);

    int ret;
    ret = inet_pton(AF_INET, svr_ip, &svr_skt_addr.sin_addr);
    svr_skt_len=sizeof(struct sockaddr_in);
    if( ret == -1)
    {
        rbl_print("UDP Client bind socket error: %s(errno: %d)\n",strerror(errno),errno);
    	return 0;
    }
   	rbl_print("UDP Client Bind socket %d successfully for port %d\r\n",skt_fd,port);
    ret = connect(skt_fd, (struct sockaddr*)&svr_skt_addr, sizeof(svr_skt_addr));
    if( ret >= 0)
    {
       	rbl_print("UDP Client connect %d successfully to IP %s\n",skt_fd,svr_ip);
       	return 0;
    }
   	rbl_print("UDP Client connect error: %s(errno: %d)\n",strerror(errno),errno);
   	close(skt_fd);
	return -1;
}
/**************************************************/
static void clt_disconnect_skt(void);
static void clt_disconnect_skt(void)
{

}
/**************************************************/
static void clt_distroy_skt(int skt_fd);
static void clt_distroy_skt(int skt_fd)
{
    if( skt_fd < 0)
    	return;
   	rbl_print("UDP Client disconnect socket %d\n",skt_fd);
   	close(skt_fd);
}
/**************************************************/
int rbl_udp_clt_init_skt(char *svr_ip,int port);
int rbl_udp_clt_init_skt(char *svr_ip,int port)
{
	int skt_fd;
    skt_fd = clt_create_skt();
    if(skt_fd < 0)
    	return -1;
    int ret;
    ret = clt_bind_skt(skt_fd,svr_ip,port);
    if(ret < 0)
    	return ret;
	ret = clt_connect_skt(skt_fd,svr_ip,port);
    if(ret < 0)
    	return ret;
	return skt_fd;
}
/**************************************************/
void rbl_udp_clt_free_skt(int skt_fd);
void rbl_udp_clt_free_skt(int skt_fd)
{
	clt_disconnect_skt();

	clt_distroy_skt(skt_fd);
}

extern void rbl_log_packet(char *data, int size);
/**************************************************/
int rbl_udp_clt_send_skt(int skt_fd,char *buf,int size);
int rbl_udp_clt_send_skt(int skt_fd,char *buf,int size)
{
	if(skt_fd < 0)
		return 0;

	int sen_len;
	sen_len = send(skt_fd, buf, size, 0);
	if(sen_len>0)
	{
		rbl_print("UDP Client Send data %d bytes!\r\n",sen_len);
		rbl_log_packet(buf, sen_len);
	}
   	return sen_len;
}
/**************************************************/
int rbl_udp_clt_recv_skt(int skt_fd,char *buf,int size);
int rbl_udp_clt_recv_skt(int skt_fd,char *buf,int size)
{
    int rec_len;

	if(skt_fd < 0)
		return 0;
    rec_len = recv(skt_fd, buf, size,0);
	if(rec_len>0)
	{
		rbl_print("UDP Client Recv data %d bytes!\r\n",rec_len);
		rbl_log_packet(buf, rec_len);
	}
   	return rec_len;
}

/**************************************************/
#include <fcntl.h>
void rbl_udp_clt_set_nonblock(int skt_fd);
void rbl_udp_clt_set_nonblock(int skt_fd)
{
	int old,new;
	old=fcntl(skt_fd,F_GETFL,0);
	new = old|O_NONBLOCK;
	fcntl(skt_fd,F_SETFL,new);
}

void rbl_udp_clt_set_block(int skt_fd);
void rbl_udp_clt_set_block(int skt_fd)
{
	int old,new;
	old=fcntl(skt_fd,F_GETFL,0);
	new = old&(~O_NONBLOCK);
	fcntl(skt_fd,F_SETFL,new);
}
/* end of clt.c */
