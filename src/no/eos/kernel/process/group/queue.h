
/*------------------------------------
 * queue.h
 * Create:  2023-02-17
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */

#ifndef SRC_KERNEL_PROC_GROUP_QUEUE_H_
#define SRC_KERNEL_PROC_GROUP_QUEUE_H_

#include "1imp.h"
/*================================================================*/
extern void	grp_ini_pro(int grp,int pro);

extern int 	grp_get_pro(int pro);
extern void	grp_add_pro(int last,int pro);
extern void	grp_del_pro(int pro);

extern int 	grp_get_next_pro(int grp,int pro);
extern void	grp_add_next_pro(int grp,int pro);
extern void	grp_del_next_pro(int grp,int pro);

extern int 	grp_get_num(int grp);
extern void grp_inc_num(int grp);
extern void grp_dec_num(int grp);
/*================================================================*/

#endif 
/* end of queue.h */
