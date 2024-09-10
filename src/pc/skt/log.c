/*
 * log.c
 *
 *  Created on: Nov 16, 2023
 *      Author: stever
 */


#include "1imp.h"
/*================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*------------------------------------*/
static void print_ascii(char c);
static void print_ascii(char c)
{
	if(c <' ')
	{
		rbl_print("%c  ", '.');
		return;
	}
	if(c<127)
	{
		rbl_print("%c  ", c);
		return;
	}
	rbl_print("%c  ", '.');
}

static void print_hex(char c);
static void print_hex(char c)
{
	int j;
	j=(int)c;
	j &= 0x000000FF;
	rbl_print("%02X ", j);
}
/*------------------------------------*/
static void print_sperator_line(void);
static void print_sperator_line(void)
{
	int i;
	rbl_print("\r\n|");
	for(i=0; i<16; i++)
		rbl_print("---");
	rbl_print("|  ");

	rbl_print("|");
	for(i=0; i<16; i++)
		rbl_print("===");
	rbl_print("|\r\n");
}

static void print_string_line(char *data,int size);
static void print_string_line(char *data,int size)
{
	int i;
	rbl_print("\r\n|");
	for(i=0; i<size; i++)
		print_hex(data[i]);
	for(i=size; i<16; i++)
		rbl_print("   ");
	rbl_print("|  ");

	rbl_print("|");
	for(i=0; i<size; i++)
		print_ascii(data[i]);
	for(i=size; i<16; i++)
		rbl_print("   ");
	rbl_print("|\r\n");
}


void rbl_log_packet(char *data, int size);
void rbl_log_packet(char *data, int size)
{
	int i,j;
	int row;
	row = size>>4;
	j = size&0x0F;
	print_sperator_line();
	for(i=0; i<row; i++)
		print_string_line(data+i*16,16);
	if(j!=0)
		print_string_line(data+row*16,j);
	print_sperator_line();
}

/*------------------------------------*/
#include <string.h>
void rbl_log_ip(char *buf,unsigned int ip_int);
void rbl_log_ip(char *buf,unsigned int ip_int)
{
	char temp[16];
	char ip[4];
	memcpy(ip,(char *)&ip_int,4);
    sprintf(temp,"%d.%d.%d.%d",ip[0], ip[1], ip[2], ip[3]);
    rbl_print("input IP address:%s\r\n",temp);
    if(buf==0x0L)
    	return;
    strcpy(buf,temp);
}
/*================================================================*/
/* end of log.c */
