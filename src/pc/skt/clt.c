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
static int app_type;
/**************************************************/
void app_clt_init_skt(int type);
void app_clt_init_skt(int type)
{
	app_type=type;
	if(app_type==1)
	{
	    tcp_clt_init_skt();
	}
	if(app_type==2)
	{
	    udp_clt_init_skt();
	}

}
/**************************************************/
void app_clt_free_skt(void);
void app_clt_free_skt(void)
{
	if(app_type==1)
	{
		tcp_clt_free_skt();
	}
	if(app_type==2)
	{
		udp_clt_free_skt();
	}
}

/**************************************************/
int app_clt_send_skt(char *buf,int size);
int app_clt_send_skt(char *buf,int size)
{
	int sen_len;
	if(app_type==1)
	{
		sen_len=tcp_clt_send_skt(buf,size);
	}
	if(app_type==2)
	{
		sen_len=udp_clt_send_skt(buf,size);
	}
   	return sen_len;
}
/**************************************************/
int app_clt_recv_skt(char *buf,int size);
int app_clt_recv_skt(char *buf,int size)
{
    int rec_len;
	if(app_type==1)
	{
		rec_len=tcp_clt_recv_skt(buf,size);
	}
	if(app_type==2)
	{
		rec_len=udp_clt_recv_skt(buf,size);
	}
   	return rec_len;
}

/**************************************************/
int app_clt_init_add(char *ip_addr);
int app_clt_init_add(char *ip_addr)
{
    int i;
	if(app_type==1)
	{
		i=tcp_clt_init_add(ip_addr);
	}
	if(app_type==2)
	{
		i=udp_clt_init_add(ip_addr);
	}
    return i;
}
/**************************************************/
#include <fcntl.h>
void app_clt_set_nonblock(void);
void app_clt_set_nonblock()
{
	if(app_type==1)
	{
		tcp_clt_set_nonblock();
	}
	if(app_type==2)
	{
		udp_clt_set_nonblock();
	}
}

void app_clt_set_block(void);
void app_clt_set_block()
{
	if(app_type==1)
	{
		tcp_clt_set_block();
	}
	if(app_type==2)
	{
		udp_clt_set_block();
	}
}
/* end of clt.c */
