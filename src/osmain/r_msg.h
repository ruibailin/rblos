#ifndef _r_msg_h
#define _r_msg_h
#include "rbltype.h"


typedef  struct{
  WORD   Head;
  WORD   Tail;
  WFAR 	*Ptr;
  BFAR 	*Pool;
}C_QUEUE;

typedef struct{
  PID   dest;
  PID   sour;
  WORD  event;
  WORD  leng;
}MSG;


#define   MAX_MSG_NUM     256
#define   MAX_POOL_LEN    MAX_MSG_NUM*(sizeof(MSG)+6)

/*------------------------------------*/
extern  VFAR  ini_self_msg(void);
extern  WFAR is_new_msg(void);
extern  BFAR *get_self_msg(void);
extern  VFAR free_self_msg(void);

extern  WORD  SendToSelf(WORD event,BFAR *out,WORD len,WORD d_pno,WORD s_pno);
/*------------------------------------*/
extern void SELF(PID FAR *self);

#endif
/*End Of r_msg.h*/


