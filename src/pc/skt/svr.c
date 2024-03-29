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
static int app_type;
/**************************************************/
void app_svr_init_skt(int type);
void app_svr_init_skt(int type)
{
	app_type=type;
	if(app_type==1)
	{
	    tcp_svr_init_skt();
	}
	if(app_type==2)
	{
	    udp_svr_init_skt();
	}
}
/**************************************************/
void app_svr_free_skt(void);
void app_svr_free_skt(void)
{
	if(app_type==1)
	{
		tcp_svr_free_skt();
	}
	if(app_type==2)
	{
		udp_svr_free_skt();
	}
}

/**************************************************/
int app_svr_send_skt(char *buf,int size);
int app_svr_send_skt(char *buf,int size)
{
	int sen_len;
	if(app_type==1)
	{
		sen_len=tcp_svr_send_skt(buf,size);
	}
	if(app_type==2)
	{
		sen_len=udp_svr_send_skt(buf,size);
	}
   	return sen_len;
}

/**************************************************/
int app_svr_recv_skt(char *buf,int size);
int app_svr_recv_skt(char *buf,int size)
{
    int rec_len;
	if(app_type==1)
	{
		rec_len=tcp_svr_recv_skt(buf,size);
	}
	if(app_type==2)
	{
		rec_len=udp_svr_recv_skt(buf,size);
	}
   	return rec_len;
}

/**************************************************/
#include <fcntl.h>
void app_svr_set_nonblock(void);
void app_svr_set_nonblock()
{
	if(app_type==1)
	{
		tcp_svr_set_nonblock();
	}
	if(app_type==2)
	{
		udp_svr_set_nonblock();
	}
}

void app_svr_set_block(void);
void app_svr_set_block()
{
	if(app_type==1)
	{
		tcp_svr_set_block();
	}
	if(app_type==2)
	{
		udp_svr_set_block();
	}
}
/* end of svr.c */
