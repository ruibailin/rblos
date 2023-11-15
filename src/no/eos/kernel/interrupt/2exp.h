/*
 * 2exp.h
 *
 *  Created on: May 19, 2023
 *      Author: stever
 */

#ifndef SRC_EOS_KERNEL_INTERRUPT_2EXP_H_
#define SRC_EOS_KERNEL_INTERRUPT_2EXP_H_
/*================================================================*/
extern void knl_set_ir_bit(int ir);
extern void knl_clr_ir_bit(int ir);
extern int knl_get_ir_bit(int ir);
extern unsigned int knl_get_ir_flag(void);
extern void knl_set_ir_flag(unsigned int flag);
/*------------------------------------*/
extern int knl_get_ir_num(void);
extern unsigned int knl_get_ir_times(void);
extern char *knl_get_ir_name(void);
extern void knl_set_ir_func(int ir,char *name, void (*entry)(void));
extern void knl_ini_ir_func(void);
extern void knl_run_ir_func(void);

/*================================================================*/
#endif /* SRC_EOS_KERNEL_INTERRUPT_2EXP_H_ */
