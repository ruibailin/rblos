#ifdef  __BORLANDC__
#include <mem.h>
#else
#include <memory.h>
#endif

#include  <dos.h>
#include  <stdlib.h>
#include  "zxj10.h"
#include  "zxhard.h"
#include  "zxtype.h"
#include  "r_mem.h"
#include  "r_msg.h"

C_QUEUE   SelfMsgBuf;
/*------------------------------------*/
void  ini_self_msg(void);
void  ini_self_msg(void)
{
  SelfMsgBuf.Send=0;
  SelfMsgBuf.Scan=0;
  SelfMsgBuf.Head=0;
  SelfMsgBuf.Tail=0;
  SelfMsgBuf.Ptr=(WORD far *)alloc_ram(MAX_MSG_NUM*sizeof(WORD));
  SelfMsgBuf.Pool=(BYTE far *)alloc_ram(MAX_POOL_LEN);
}
/*------------------------------------*/
BYTE  far *get_self_msg(void);
BYTE  far *get_self_msg()
{
  WORD  offset;
  BYTE  far *ptr;

  SelfMsgBuf.Scan++;
  _disable();
  offset=SelfMsgBuf.Ptr[SelfMsgBuf.Tail];
  ptr=SelfMsgBuf.Pool+offset;
  _enable();
  return((BYTE far *)ptr);
}
/*------------------------------------*/
void  free_self_msg(void);
void  free_self_msg()
{
  _disable();
  SelfMsgBuf.Tail++;
  if(SelfMsgBuf.Tail==MAX_MSG_NUM)
  SelfMsgBuf.Tail=0;
  _enable();
}
/*------------------------------------*/
BYTE  far *req_self_buf(WORD len);
BYTE  far *req_self_buf(WORD len)
{
  WORD  ii;
  WORD  HeadMsgPtr,TailMsgPtr;
  BYTE  far *ptr;
  ptr=SelfMsgBuf.Pool;

  ii=SelfMsgBuf.Head;
  ii++;
  if(ii==MAX_MSG_NUM)  ii=0;
  if(ii==SelfMsgBuf.Tail)
  return(NULL);                              /*No more Ptr*/

  HeadMsgPtr=SelfMsgBuf.Ptr[SelfMsgBuf.Head];  /*Point to Useable Buffer */
  TailMsgPtr=SelfMsgBuf.Ptr[SelfMsgBuf.Tail];  /*Point to Unuseable Buffer */

  if(HeadMsgPtr<TailMsgPtr)
  {
    ii=TailMsgPtr-HeadMsgPtr;
    if(ii>len)
    goto  FindUB;
    return(NULL);
  }
  else                          /* HeadMsgPtr>=TailMsgPtr */
  {
    ii=MAX_POOL_LEN-HeadMsgPtr;
    if(ii>len)
    goto FindUB;
    if(TailMsgPtr>len)
    {
      HeadMsgPtr=0;                /*Current Useable Offset become to be 0*/
      SelfMsgBuf.Ptr[SelfMsgBuf.Head]=0;
      goto FindUB;
    }
    return(NULL);
  }

FindUB:
  SelfMsgBuf.Send++;
  ptr += HeadMsgPtr;
  HeadMsgPtr += len;
  SelfMsgBuf.Head++;
  if(SelfMsgBuf.Head==MAX_MSG_NUM)
  SelfMsgBuf.Head=0;
  SelfMsgBuf.Ptr[SelfMsgBuf.Head]=HeadMsgPtr; /*Next Useable Buffer */
  return((BYTE far *)ptr);
}

/*===========================================================================*/
WORD SysCurPno=0;
/*------------------------------------*/
WORD SendToSelf(WORD event,BYTE  far *out,WORD len,WORD dest,WORD sour);
WORD SendToSelf(WORD event,BYTE  far *out,WORD len,WORD dest,WORD sour)
{
  BYTE far *HeadPtr;
  BYTE maste,slave;

  maste=_GetEXRegByte(DOS_OCW1M);
  slave=_GetEXRegByte(DOS_OCW1S);
  _SetEXRegByte(DOS_OCW1M,0xfb);
  _SetEXRegByte(DOS_OCW1S,0xff);
  HeadPtr=req_self_buf(sizeof(MSG)+len);
  _SetEXRegByte(DOS_OCW1S,slave);
  _SetEXRegByte(DOS_OCW1M,maste);
  if(HeadPtr==NULL)
  return(R01_OTHER_ERROR);

  ((MSG far *)HeadPtr)->dest.pno=dest;
  ((MSG far *)HeadPtr)->sour.pno=sour;
  ((MSG far *)HeadPtr)->sour.unit=2;
  ((MSG far *)HeadPtr)->event=event;
  ((MSG far *)HeadPtr)->leng=len;
  HeadPtr += sizeof(MSG);
  _fmemcpy(HeadPtr,out,len);
  return(R01_SUCCESS);
}
/*===========================================================================*/
WORD (far *sys_mp_com)(WORD event,BYTE  far *out,WORD len,WORD dest,WORD sour)=&SendToSelf;
WORD (far *sys_pp_com)(WORD event,BYTE  far *out,WORD len,WORD dest,WORD sour)=&SendToSelf;
WORD (far *sys_self_com)(WORD event,BYTE  far *out,WORD len,WORD dest,WORD sour)=&SendToSelf;
/*------------------------------------*/
WORD MSEND(WORD event,BYTE  far *out,WORD len,PID dest);
WORD MSEND(WORD event,BYTE  far *out,WORD len,PID dest)
{
  return(sys_pp_com(event,out,len,dest.pno,SysCurPno));
}
/*------------------------------------*/
WORD mp_com_state=5;
WORD ASEND(WORD event,BYTE  far *out,WORD len,PID dest);
WORD ASEND(WORD event,BYTE  far *out,WORD len,PID dest)
{
  WORD result;
  if(dest.unit == 0)
  {
    result=sys_mp_com(event,out,len,dest.pno,SysCurPno);
    if(result)
    {
      mp_com_state=50;
      return(R01_SUCCESS);
    }
    else
    {
      mp_com_state=5;
      if(SysCurPno<32)
      sys_self_com(event,out,len,dest.pno+32,SysCurPno);
      return(R01_PPCOMM_ABORT);
    }
  }
  if(dest.unit < 0x80)
    return(sys_self_com(event,out,len,dest.pno,SysCurPno));
  else
    return(sys_pp_com(event,out,len,dest.pno,SysCurPno));
}
/*End Of mmem.c*/
