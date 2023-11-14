#ifndef _r_msg_h
#define _r_msg_h

#define   MAX_MSG_NUM     512
#define   MAX_POOL_LEN    MAX_MSG_NUM*(sizeof(MSG)+sizeof(SLN))

typedef  struct{
  WORD   Send;            /*Test*/
  WORD   Scan;

  WORD   Head;
  WORD   Tail;
  WORD   far *Ptr;
  BYTE   far *Pool;
}C_QUEUE;

typedef struct{
  PID   dest;
  PID   sour;
  WORD  event;
  WORD  leng;
}MSG;

/*------------------------------------*/
extern  void  far  ini_self_msg(void);
extern  BYTE  far *get_self_msg(void);
extern  void  far free_self_msg(void);
extern  BYTE  far *req_self_buf(WORD len);
extern  WORD  SendToSelf(WORD event,BYTE  far *out,WORD len,WORD d_pno,WORD s_pno);
/*------------------------------------*/
extern  WORD      SysCurPno;
extern  C_QUEUE   SelfMsgBuf;
extern  WORD (far *sys_mp_com)(WORD event,BYTE  far *out,WORD len,WORD d_pno,WORD s_pno);
extern  WORD (far *sys_pp_com)(WORD event,BYTE  far *out,WORD len,WORD d_pno,WORD s_pno);
#endif

/*End Of r_msg.h*/
