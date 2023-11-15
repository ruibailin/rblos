
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
extern	int		SELF(void);
extern	int		STATE(void);
extern	void	NEXT_STATE(int state);
extern	int		EVENT(void);
extern	int		LENGTH(void);
extern	int		SENDER(void);
extern	void	ASEND(int dest,int event,int len,void *in);
extern	void	SET(int ptno,int len);
extern	void	KILL(int ptno);

/*================================================================*/
#endif
/* end of r_func.h */
