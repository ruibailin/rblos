#ifdef  __BORLANDC__
#include <mem.h>
#else
#include <memory.h>
#endif

#include <dos.h>
#include "zxj10.h"
#include "zxevent.h"
#include "r_mem.h"
#include "zxfunc.h"

/*------------------------------------*/
typedef struct{
  BYTE  far *ptr;   /*address*/
  BYTE  len;        /*length*/
}SHOWRAM;

typedef struct{
  BYTE  far *ptr;   /*Segment of ROM or ROM*/
  BYTE  len;        /*length*/
  BYTE  buf[128];
}UPDATERAM;

/*------------------------------------*/
static void far  DisplayRamFunc(SHOWRAM far *in);
static void far  DisplayRamFunc(SHOWRAM far *in)
{
  BYTE ii,len;
  PID  spid;
  UPDATERAM  out;
  BYTE far *sptr;
  BYTE far *dptr;
  out.ptr=in->ptr;
  out.len=in->len;

  len=in->len;
  sptr=in->ptr;
  dptr=(BYTE far *)&(out.buf[0]);
  for(ii=0;ii<len;ii++)
  dptr[ii]=sptr[ii];

  SENDER((PID far *)&spid);
  ASEND(DisplayRamEvent,(BYTE far *)&out,(WORD)sizeof(out),spid);
}

/*------------------------------------*/
static void far  UpDateRamFunc(UPDATERAM far *in);
static void far  UpDateRamFunc(UPDATERAM far *in)
{
  BYTE len;
  BYTE ii;
  PID  spid;
  BYTE far *sptr;
  BYTE far *dptr;

  len=in->len;
  dptr=in->ptr;
  sptr=(BYTE far *)&(in->buf[0]);
  for(ii=0;ii<len;ii++)
  dptr[ii]=sptr[ii];

  SENDER((PID far *)&spid);
  ASEND(UpDateRamEvent,(BYTE far *)&spid,(WORD)4,spid);
}

/*------------------------------------*/
void  far R01MMLMgt(void far *in);
void  far R01MMLMgt(void far *in)
{
  WORD ss,ee;
  PID  spid;
  void (far *entry)(void);
  ss=STATE();
  ee=EVENT();

  switch(ee)
  {
    case  DisplayRamEvent:
          DisplayRamFunc((SHOWRAM far *)in);
          break;
    case  UpDateRamEvent:
          UpDateRamFunc((UPDATERAM far *)in);
          break;

    case  ReqBackMsgEvent:      /*Transfer Send The MSG*/
          SENDER((PID far *)&spid);
          ss=LENGTH();
          ASEND(BackMsgAckEvent,(BYTE far *)in,ss,spid);
          break;

    case  RestartEvent:
          _disable();
          (long)entry=0xf0000000l;
          entry();
          break;
    case  ResetAplication:
          (long)entry=0xc0000000l;
          entry();
          break;
    default:
          break;
  }
}

/*End Of zxmml.c */
