
/*------------------------------------
 * r_pat.h
 * Create:  2021-10-17
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */


#include "0ctr.h"
#ifndef	EOS_KERNEL_R_PAT_H_
#define EOS_KERNEL_R_PAT_H_
/*================================================================*/
extern	void	ini_pat_table(void);
extern	int		get_pat_tno(int pno);
extern	void	set_pat_tno(int pno,int tno);
extern	void	set_pat_entry(int  pno,void (*entry)(void *));
extern	void	*get_pat_entry(int  pno);
extern	void	run_pat_entry(int  pno,void *in);

/*================================================================*/
#endif
/* end of r_pat.h */
