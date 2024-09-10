/*
 * test_skt.c
 *
 *  Created on: Sep 9, 2024
 *      Author: stever
 */

#include <stdio.h>
#include "clt.h"
#include "svr.h"
#include "log.h"
/*================================================================*/
int svr_clt;
int main_type;
char main_ip[16];
int main_port;

static char ac_cc[]={0x41,0x43,0xCC,0x00,0x66,0x51,0x01,0x01,0x04,0x00,0x04,0x00,0x02,0x00,0x70,0x87,0x00};
static char rec[480];
static int skt_fd=-1;
static int cnct_fd=-1;
static void test_clt()
{
	int ret;
	if(skt_fd < 0)
	{
		skt_fd = rbl_clt_init_skt(main_type,main_ip,main_port);
		rbl_clt_set_nonblock(main_type,skt_fd);
		return;
	}
	else
	{
		ret=rbl_clt_send_skt(main_type,skt_fd,ac_cc,16);
		if(ret!=16)
			printf("Client Wrong send \r\n");
		while(1)
		{
			ret=rbl_clt_recv_skt(main_type,skt_fd,rec,480);
			if(ret>0)
			{
				printf(" Recv %d \r\n",ret);
				rbl_log_packet(rec,ret);
				break;
			}
		}
	}
}

static struct sockaddr udp_clt_addr;
static void test_svr()
{
	int ret;
	if(skt_fd<0)
	{
		skt_fd = rbl_svr_init_skt(main_type,main_port);
		rbl_svr_set_nonblock(main_type,skt_fd);
		cnct_fd = rbl_svr_conn_skt(main_type,skt_fd,&udp_clt_addr);
		printf("blocked 1\r\n");
		return;
	}
	else if(cnct_fd<0)
	{
		cnct_fd = rbl_svr_conn_skt(main_type,skt_fd,&udp_clt_addr);
		printf("blocked 2\r\n");
	}
	else
	{
		ret=rbl_svr_recv_skt(main_type,skt_fd,cnct_fd,rec,480,(struct sockaddr *)&udp_clt_addr);
		if(ret < 1)
			return;
		rbl_log_packet(rec,ret);
		ret=rbl_svr_send_skt(main_type,skt_fd,cnct_fd,ac_cc,16,(struct sockaddr *)&udp_clt_addr);
		if(ret!=16)
			printf("Server Wrong send \r\n");
	}
}
/*================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int get_type(char *cc);
static int get_type(char *cc)
{
	int len,ret;
	len = strlen(cc);
	if(len == 1)
	{
		if(cc[0] == '1')
			return 1;
		if(cc[0] == '2')
			return 2;
		return 0;
	}
	if(len != 3)
		return 0;
	ret = strcmp(cc,"TCP");
	if(ret == 0)
		return 1;
	ret = strcmp(cc,"UDP");
	if(ret == 0)
		return 2;
	return 0;
}

static int get_ip(char *ip_str,char *cc);
static int get_ip(char *ip_str,char *cc)
{
	int ip[4];
	sscanf(cc,"%d.%d.%d.%d",&ip[0],&ip[1],&ip[2],&ip[3]);
	sprintf(ip_str,"%d.%d.%d.%d",ip[0],ip[1],ip[2],ip[3]);
	return 4;
}
/*------------------------------------*/
void test_skt(int argc, char **argv);
void test_skt(int argc, char **argv)
{
	int i;
	for(i=0;i<argc;i++)
		printf("Input %d %s\r\n",i,argv[i]);
	if(argc < 5)
	{
		printf("no enough input\r\n");
		printf("Usage:\r\n");
		printf("1: mode,0 server or 1 client\r\n");
		printf("2: type,1/TCP tcp or 2/UDP udp\r\n");
		printf("3: Server IP Address, no use in server mode\r\n");
		printf("4: port number\r\n");
	}

	svr_clt = atoi(argv[1]);
	if(svr_clt == 0)
		printf("Sever Mode\r\n");
	else if(svr_clt == 1)
		printf("Client Mode\r\n");
	else
	{
		printf("Wrong Mode\r\n");
		return;
	}

	main_type = get_type(argv[2]);
	if(main_type == 1)
		printf("Socket Type:TCP\r\n");
	else if(main_type == 2)
		printf("Socket Type:UDP\r\n");
	else
	{
		printf("Wrong Socket Type!\r\n");
		return;
	}

	get_ip(main_ip,argv[3]);
	printf("Server IP address:%s\r\n",main_ip);
	main_port = atoi(argv[4]);
	printf("Server IP port:%d\r\n",main_port);

	unsigned int ii;
	ii = 0;
	while(1)
	{
		ii ++;
		if(ii<0x8000000)
			continue;
		ii = 0;
		if(svr_clt == 0)
			test_svr();
		else
			test_clt();
	}
}
/*================================================================*/
/* end of test_skt.c */
