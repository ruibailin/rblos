
/*------------------------------------
 * eos_api.h
 * Create:  2023-02-21
 * Author:  Steve Rui
 *------------------------------------
 * Record:
 *
 *
 *
 *
 *------------------------------------
 */


/*================================================================*/
#ifndef SRC_NO_EOS_EOS_H_
#define SRC_NO_EOS_EOS_H_
/*================================================================*/
extern	int		EOS_SELF(void);
#define eos_get_self_pid EOS_SELF
extern	int		EOS_STATE(void);
#define eos_get_state EOS_STATE
extern	void	EOS_NEXT(int state);
#define eos_set_state EOS_NEXT
extern	int		EOS_EVENT(void);
#define eos_get_event EOS_EVENT
extern	int		EOS_LENGTH(void);
#define eos_get_length EOS_LENGTH
extern	int		EOS_SENDER(void);
#define eos_get_sender_pid EOS_SENDER
extern	void	EOS_ASEND(int dest,int event,int len,void *in);
#define eos_async_send EOS_ASEND
extern	void	EOS_SET(int ptno,int len);
extern  void eos_set_timer(int length);
#define eos_set_timer_ex EOS_SET
extern	void	EOS_KILL(int ptno);
extern  void eos_reset_timer(void);
#define eos_reset_timer_ex EOS_KILL
#define eos_clr_timer eos_reset_timer
#define eos_clr_timer_ex EOS_KILL

extern  int eos_create_real(char *name,void (*entry)(void *));
extern  int eos_create_time(char *name,void (*entry)(void *),int interval);
extern  int eos_create_idle(char *name,void (*entry)(void *));
extern  void *eos_get_data(void);
extern  void eos_set_data(void *data);
extern  int eos_get_parent_pid(void);
/*================================================================*/
#endif

/* end of eos_api.h */
