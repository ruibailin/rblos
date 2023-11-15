/*
 * func.c
 *
 *  Created on: May 19, 2023
 *      Author: stever
 */


#include "1imp.h"
/*================================================================*/
typedef struct{
	unsigned int times;
	char *name;
    void (*entry)(void);
}IRT;
/*------------------------------------*/
static IRT knl_irt[MAX_IR_NUM];
static int knl_now_ir;
static char *null_ir_name="Null";
static void null_ir_func(void);
static void null_ir_func()
{

}
/*------------------------------------*/
int knl_get_ir_num(void);
int knl_get_ir_num()
{
	return knl_now_ir;
}
unsigned int knl_get_ir_times(void);
unsigned int knl_get_ir_times()
{
	return knl_irt[knl_now_ir].times;
}

char *knl_get_ir_name(void);
char *knl_get_ir_name()
{
	return knl_irt[knl_now_ir].name;
}
/*------------------------------------*/
void knl_set_ir_func(int ir,char *name, void (*entry)(void));
void knl_set_ir_func(int ir,char *name, void (*entry)(void))
{
	if(ir>MAX_IR_NUM-1)
		return;
	knl_irt[ir].name=name;
	knl_irt[ir].entry=entry;
}

static void run_ir_func(int ir);
static void run_ir_func(int ir)
{
	knl_irt[ir].entry();
}
/*------------------------------------*/
extern int knl_get_ir_bit(int ir);
extern void knl_clr_ir_bit(int ir);
void knl_ini_ir_func(void);
void knl_ini_ir_func()
{
	int i;
	for(i=0;i<MAX_IR_NUM;i++)
	{
		knl_irt[i].times=0;
		knl_irt[i].name=null_ir_name;
		knl_irt[i].entry=null_ir_func;
	}
}

void knl_run_ir_func(void);
void knl_run_ir_func()
{
	int i;
	for(i=0;i<MAX_IR_NUM;i++)
	{
		if(!knl_get_ir_bit(i))
			continue;
		knl_clr_ir_bit(i);
		knl_irt[i].times++;
		knl_now_ir=i;
		run_ir_func(i);
	}
}

/*================================================================*/
/* end of func.c */
