/*
 * r_pat.h
 *
 *  Created on: Apr 13, 2021
 *      Author: steve
 */

#ifndef SRC_NO_KERNEL_R_PAT_H_
#define SRC_NO_KERNEL_R_PAT_H_
#include "1imp.h"
/*================================================================*/
extern	int		get_pat_tno(int pno);
extern	void	set_pat_tno(int pno,int tno);
extern	void	set_pat_entry(int  pno,void *entry);
extern	void	*get_pat_entry(int  pno);
/*================================================================*/
#endif /* SRC_NO_KERNEL_R_PAT_H_ */
