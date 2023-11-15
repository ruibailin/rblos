
/*------------------------------------
 * 2exp.h
 * Create:  2023-02-18
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */

#ifndef KERNEL_PROC_GROUP_2EXP_H_
#define KERNEL_PROC_GROUP_2EXP_H_


/*================================================================*/
extern void grp_ini_pro(void);

extern void grp_add_dum_pro(int pno);
extern void grp_del_dum_pro(int pno);
extern void grp_ini_dum_pro(void);
extern int  grp_get_dum_pro(void);


extern void grp_add_idle_pro(int pno);
extern void grp_del_idle_pro(int pno);
extern void grp_ini_idle_pro(void);
extern void	grp_run_idle_pro(void);

extern void grp_add_msg_pro(int pno);
extern void grp_del_msg_pro(int pno);
extern void grp_ini_msg_pro(void);
extern int	grp_run_msg_pro(void);

extern void grp_add_slot_pro(int pno);
extern void grp_del_slot_pro(int pno);
extern void grp_ini_slot_pro(void);
extern int	grp_run_slot_pro(void);

extern void grp_add_time_pro(int pno);
extern void grp_del_time_pro(int pno);
extern void grp_ini_time_pro(void);
extern int	grp_run_time_pro(void);

extern void grp_add_real_pro(int pno);
extern void grp_del_real_pro(int pno);
extern void grp_ini_real_pro(void);
extern void	grp_run_real_pro(void);

extern int 	grp_get_next_pro(int grp,int pro);
extern void	grp_add_next_pro(int grp,int pro);
extern void	grp_del_next_pro(int grp,int pro);
/*================================================================*/

#endif 
/* end of 2exp.h */
