/*
 * flag.c
 *
 *  Created on: May 19, 2023
 *      Author: stever
 */


#include "1imp.h"
/*================================================================*/
static	unsigned int knl_ir_flag=0;
static  unsigned int knl_ir_error=0;
/*------------------------------------*/
void knl_set_ir_bit(int ir);
void knl_set_ir_bit(int ir)
{
	unsigned int mask,temp;
	mask=1;
	mask <<= ir;
	temp = knl_ir_flag & mask;
	if(temp!=0)
		knl_ir_error++;		//for test.
	knl_ir_flag |= mask;
}

extern void cpu_disable_irq_all(void);
extern void cpu_enable_irq_all(void);
void knl_clr_ir_bit(int ir);
void knl_clr_ir_bit(int ir)
{
	unsigned int mask;
	mask=1;
	mask <<= ir;
	mask = ~mask;
	cpu_disable_irq_all();
	knl_ir_flag &= mask;
	cpu_enable_irq_all();
}

int knl_get_ir_bit(int ir);
int knl_get_ir_bit(int ir)
{
	unsigned int mask;
	mask=1;
	mask <<= ir;
	mask &= knl_ir_flag;
	if(mask == 0)
		return 0;
	else
		return 1;
}


unsigned int knl_get_ir_flag(void);
unsigned int knl_get_ir_flag()
{
	return knl_ir_flag;
}

void knl_set_ir_flag(unsigned int flag);
void knl_set_ir_flag(unsigned int flag)
{
	cpu_disable_irq_all();
	knl_ir_flag=flag;
	cpu_enable_irq_all();
}
/*================================================================*/
/* end of flag.c */
