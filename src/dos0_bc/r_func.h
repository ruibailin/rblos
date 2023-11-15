/***操作系统原语*/
#ifndef _r_func_h
#define _r_func_h

extern	int		SELF(void);
extern	int		STATE(void);
extern	void	NEXT_STATE(int ss);
extern	int		EVENT(void);
extern	int		LENGTH(void);
extern	int		SENDER(void);
extern	void	ASEND(int dd,int ee,int ll,void *in);
extern	void	SET(int tno,int ll);
extern	void	KILL(int tno);

#endif

