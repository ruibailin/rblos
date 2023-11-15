
/*------------------------------------
 * r_func.h
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
#ifndef EOS_KERNEL_R_FUNC_H_
#define EOS_KERNEL_R_FUNC_H_
/*================================================================*/
extern	int		EOS_SELF(void);
extern	int		EOS_STATE(void);
extern	void	EOS_NEXT(int state);
extern	int		EOS_EVENT(void);
extern	int		EOS_LENGTH(void);
extern	int		EOS_SENDER(void);
extern	void	EOS_ASEND(int dest,int event,int len,void *in);
extern	void	EOS_SET(int ptno,int len);
extern	void	EOS_KILL(int ptno);

/*================================================================*/
#endif
/* end of r_func.h */
