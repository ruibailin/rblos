
/*------------------------------------
 * eos.h
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
#ifndef SRC_NO_EOS_EOS_H_
#define SRC_NO_EOS_EOS_H_
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
/* end of eos.h */
