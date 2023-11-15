#include  "rbltype.h"
#include  "r_mem.h"
#include  "r_msg.h"

static C_QUEUE   SelfMsgBuf;
/*------------------------------------*/
void  ini_self_msg(void);
void  ini_self_msg(void)
{
  SelfMsgBuf.Head=0;
  SelfMsgBuf.Tail=0;
  SelfMsgBuf.Ptr=(WFAR *)alloc_ram(MAX_MSG_NUM*sizeof(WORD));
  SelfMsgBuf.Pool=(BFAR *)alloc_ram(MAX_POOL_LEN);
 }

/*------------------------------------*/

WFAR is_new_msg(void);
WFAR is_new_msg(void)
{
	if(SelfMsgBuf.Head==SelfMsgBuf.Tail) return 0;
	else return 1;
}



/*------------------------------------*/
BFAR *get_self_msg(void);
BFAR *get_self_msg()
{
  WORD  offset;
  BFAR *ptr;
  cli_int();
  offset=SelfMsgBuf.Ptr[SelfMsgBuf.Tail];
  ptr=SelfMsgBuf.Pool+offset;
  sti_int();

  return((BFAR *)ptr);
}
/*------------------------------------*/
void  free_self_msg(void);
void  free_self_msg()
{
  cli_int();
  SelfMsgBuf.Tail++;
  if(SelfMsgBuf.Tail==MAX_MSG_NUM)
  SelfMsgBuf.Tail=0;
  sti_int();

}
/*------------------------------------*/
static BFAR *req_self_buf(WORD len);
static BFAR *req_self_buf(WORD len)
{
  WORD  ii;
  WORD  HeadMsgPtr,TailMsgPtr;
  BFAR *ptr;
  ptr=SelfMsgBuf.Pool;

  ii=SelfMsgBuf.Head;
  ii++;
  if(ii==MAX_MSG_NUM)  ii=0;
  if(ii==SelfMsgBuf.Tail)
  return((VFAR *)0);                              /*No more Ptr*/

  HeadMsgPtr=SelfMsgBuf.Ptr[SelfMsgBuf.Head];  /*Point to Useable Buffer */
  TailMsgPtr=SelfMsgBuf.Ptr[SelfMsgBuf.Tail];  /*Point to Unuseable Buffer */

  if(HeadMsgPtr<TailMsgPtr)
  {
    ii=TailMsgPtr-HeadMsgPtr;
    if(ii>len)
    goto  FindUB;
    return((VFAR *)0);
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
    return((VFAR *)0);
  }

FindUB:
  ptr += HeadMsgPtr;
  HeadMsgPtr += len;
  SelfMsgBuf.Head++;
  if(SelfMsgBuf.Head==MAX_MSG_NUM)
  SelfMsgBuf.Head=0;
  SelfMsgBuf.Ptr[SelfMsgBuf.Head]=HeadMsgPtr; /*Next Useable Buffer */
  return((BFAR *)ptr);
}

/*===========================================================================*/

/*------------------------------------*/
WORD SendToSelf(WORD event,BFAR *out,WORD len,WORD dest,WORD sour);
WORD SendToSelf(WORD event,BFAR *out,WORD len,WORD dest,WORD sour)
{
  BFAR *HeadPtr;
  WORD ii;
  cli_int();
  HeadPtr=req_self_buf(sizeof(MSG)+len);
  sti_int();
  if(HeadPtr==(VFAR *)0)
  return(0);

  ((MSG FAR *)HeadPtr)->dest.pno=dest;
  ((MSG FAR *)HeadPtr)->dest.unit=0;
  ((MSG FAR *)HeadPtr)->dest.module =0;
  ((MSG FAR *)HeadPtr)->sour.pno=sour;
  ((MSG FAR *)HeadPtr)->sour.unit=0;
  ((MSG FAR *)HeadPtr)->sour.module=0;
  ((MSG FAR *)HeadPtr)->event=event;
  ((MSG FAR *)HeadPtr)->leng=len;
  HeadPtr += sizeof(MSG);
  for(ii=0;ii<len;ii++)
  {
  	(BFAR)HeadPtr[ii]=(BFAR)out[ii];
  }
  send_ret();
  return(1);
}
/*===========================================================================*/
WORD MSEND(WORD event,BFAR *out,WORD len,PID *dest);
WORD MSEND(WORD event,BFAR *out,WORD len,PID *dest)
{
	PID	self;
	SELF(&self);
	return(SendToSelf(event,out,len,dest->pno,self.pno));
}
WORD ASEND(WORD event,BFAR *out,WORD len,PID *dest);
WORD ASEND(WORD event,BFAR *out,WORD len,PID *dest)
{
	PID	self;
	SELF(&self);
	return(SendToSelf(event,out,len,dest->pno,self.pno));
}
/*End Of mmem.c*/
