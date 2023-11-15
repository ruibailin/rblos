/*
 * r_func.h
 *
 *  Created on: Apr 13, 2021
 *      Author: steve
 */

#ifndef SRC_NO_KERNEL_R_FUNC_H_
#define SRC_NO_KERNEL_R_FUNC_H_
#include "1imp.h"
/*================================================================*/
extern	int		SELF(void);
extern	int		STATE(void);
extern	void	NEXT_STATE(int ss);
extern	int		EVENT(void);
extern	int		LENGTH(void);
extern	int		SENDER(void);
extern	void	ASEND(int dd,int ee,int ll,void *in);
extern	void	SET(int tno,int ll);
extern	void	KILL(int tno);

/*================================================================*/
#endif /* SRC_NO_KERNEL_R_FUNC_H_ */
