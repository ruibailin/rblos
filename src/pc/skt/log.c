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
#define aci_print(x...)  	printf(x)
#define lte_print(x...)  	printf(x)
/*------------------------------------*/
static void print_ascii(char c);
static void print_ascii(char c)
{
	if(c <' ')
	{
		lte_print("%c  ", '.');
		return;
	}
	if(c<127)
	{
		lte_print("%c  ", c);
		return;
	}
	lte_print("%c  ", '.');
}

static void print_hex(char c);
static void print_hex(char c)
{
	int j;
	j=(int)c;
	j &= 0x000000FF;
	aci_print("%02X ", j);
}
/*------------------------------------*/
static void print_sperator_line(void);
static void print_sperator_line(void)
{
	int i;
	aci_print("\r\n|");
	for(i=0; i<16; i++)
		aci_print("---");
	aci_print("|  ");

	aci_print("|");
	for(i=0; i<16; i++)
		aci_print("===");
	aci_print("|\r\n");
}

static void print_string_line(char *data,int size);
static void print_string_line(char *data,int size)
{
	int i;
	aci_print("\r\n|");
	for(i=0; i<size; i++)
		print_hex(data[i]);
	for(i=size; i<16; i++)
		aci_print("   ");
	aci_print("|  ");

	aci_print("|");
	for(i=0; i<size; i++)
		print_ascii(data[i]);
	for(i=size; i<16; i++)
		aci_print("   ");
	aci_print("|\r\n");
}


void skt_log_packet(char *data, int size);
void skt_log_packet(char *data, int size)
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

void skt_log_hex(char data);
void skt_log_hex(char data)
{
	print_hex(data);
}

void skt_log_ascii(char data);
void skt_log_ascii(char data)
{
	print_ascii(data);
}
/*================================================================*/
/* end of log.c */
