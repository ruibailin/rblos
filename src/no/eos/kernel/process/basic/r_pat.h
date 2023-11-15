
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


#include "1imp.h"

#define EOS_KERNEL_R_PAT_H_
/*================================================================*/
extern	int		get_pat_tno(int pno);
extern	void	set_pat_tno(int pno,int tno);
extern	int		get_pat_attr(int pno);
extern	void	set_pat_attr(int pno,int tno);
extern  char 	*get_pat_name(int  pno);
extern  void 	set_pat_name(int  pno,char *name);
extern	void	set_pat_entry(int  pno,void (*entry)(void *));
extern	void	*get_pat_entry(int  pno);
extern	void	run_pat_entry(int  pno,void *in);

/*================================================================*/
/* end of r_pat.h */
