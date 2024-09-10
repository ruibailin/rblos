/*
 * skt_clt.c
 *
 *  Created on: Sep 10, 2024
 *      Author: stever
 */


/*================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
/*------------------------------------*/
unsigned int rbl_skt_get_ip_addr(void *clt_info);
unsigned int rbl_skt_get_ip_addr(void *clt_info)
{
	struct sockaddr *addr;
	addr = (struct sockaddr *)clt_info;
	unsigned int ip,temp;
	ip = 0;
	temp = addr->sa_data[2];
	ip += temp<<24;
	temp = addr->sa_data[3];
	ip += temp<<16;
	temp = addr->sa_data[4];
	ip += temp<<8;
	temp = addr->sa_data[5];
	ip += temp;
	return ip;
}
int rbl_skt_get_ip_port(void *clt_info);
int rbl_skt_get_ip_port(void *clt_info)
{
	struct sockaddr *addr;
	addr = (struct sockaddr *)clt_info;
	unsigned int port,temp;
	port = 0;
	temp = addr->sa_data[0];
	port += temp<<8;
	temp = addr->sa_data[1];
	port += temp;
	return port;
}

#include <string.h>
void rbl_skt_get_ip_string(void *clt_info,char *ip_str);
void rbl_skt_get_ip_string(void *clt_info,char *ip_str)
{
	struct sockaddr *addr;
	addr = (struct sockaddr *)clt_info;
	char ip_addr[24];
	unsigned int port;
	port = addr->sa_data[0];
	port <<= 8;
	port += addr->sa_data[1];
	port &= 0xFFFF;
	sprintf(ip_addr,"%d.%d.%d.%d",addr->sa_data[2],addr->sa_data[3],addr->sa_data[4],addr->sa_data[5]);
	strcpy(ip_str,ip_addr);
}
/*================================================================*/
/* end of skt_clt.c */
