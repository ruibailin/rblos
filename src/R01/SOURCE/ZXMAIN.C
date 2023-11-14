/****************** __MICROSOFT__ ****************/
#include <dos.h>

#include  "zxj10.h"
#include  "zxfunc.h"
#include  "r_msg.h"
#include  "r_pcb.h"
#include  "r_tcb.h"

/*______________________________________*/
void far IniAll(void);
void far MainLoop(void);

extern void far Ini386(void);         /*Module: zxhard.c*/
int main()
{
  Ini386();
  IniAll();
  _enable();
  MainLoop();
  return 0;
}
/*------------------------------------*/
void interrupt far oldThandler(void);
void interrupt far oldThandler()
{
  _disable();
  outp((unsigned short)0x20,(unsigned char)0x20);
  outp((unsigned short)0xa0,(unsigned char)0x20);
  _enable();
}
/*------------------------------------*/
typedef  struct{
  WORD  ms10;       /*Count Of 10 ms */
  WORD  ms100;
  WORD  second;
  WORD  minute;
  WORD  hour;
}COUNT;
/*------------------------------------*/
long  SysRunTime=0;
long  CurRunTime=0;
#define MAX_EXE_TIME  134000
long  get_cpu_rate(void);
long  get_cpu_rate()
{
  return(SysRunTime);
}
/*---------------------------------*/
static  COUNT SysTimeDate;
static  COUNT CurTimeDate;
/*------------------------------------*/
long  get_sys_tick(void);
long  get_sys_tick()
{
  long SysTicks;
  SysTicks  = SysTimeDate.hour;
  SysTicks *= 60;
  SysTicks += SysTimeDate.minute;
  SysTicks *= 60;
  SysTicks += SysTimeDate.second;
  SysTicks *= 10;
  SysTicks += SysTimeDate.ms100;
  SysTicks *= 10;
  SysTicks += SysTimeDate.ms10;
  return(SysTicks);
}
/*------------------------------------*/
static  void  deal_sys_date(void);
static  void  deal_sys_date()
{
  SysTimeDate.ms10++;
  if(SysTimeDate.ms10!=10)  return;
  SysTimeDate.ms10=0;
  SysTimeDate.ms100++;
  if(SysTimeDate.ms100!=10)  return;
  SysTimeDate.ms100=0;
  SysTimeDate.second++;
  SysRunTime=CurRunTime;      /*Calculate CPU Busy Rate*/
  CurRunTime=0;
  if(SysTimeDate.second!=60)  return;
  SysTimeDate.second=0;
  SysTimeDate.minute++;
  if(SysTimeDate.minute!=60)  return;
  SysTimeDate.minute=0;
  SysTimeDate.hour++;
}
/*------------------------------------*/
extern  WORD  SysCurPno;
void interrupt far newThandler(void);
void interrupt far newThandler()
{
  WORD  BufCurPno;
  _disable();
  run_tcb_queue();
  deal_sys_date();
  BufCurPno=SysCurPno;
  run_pcb_queue(Pro0msQueue);                 /*Real Time*/
  SysCurPno=BufCurPno;
  outp((unsigned short)0x20,(unsigned char)0x20);
  outp((unsigned short)0xa0,(unsigned char)0x20);
  _enable();
}
/*------------------------------------*/
static  void SetVector(WORD, void far *);
static  void SetVector(WORD num, void far *in)
{
  long  far *ptr;
  #ifdef  __BORLANDC__
  if(num != 0x08)
  return;
  num=0x1c;
  #endif
  (long)ptr = num*4;
  *ptr=(long)in;
}
/*------------------------------------*/
extern WORD far SendToMP(WORD event,BYTE far * Data,WORD len,WORD d_pno,WORD s_pno);
void   IniAll(void)
{
  WORD  ii;
  clear_watch_dog();
  #ifndef  __BORLANDC__
  for(ii=0;ii<128;ii++)
  SetVector(ii,(void far *)oldThandler);
  sys_mp_com=&SendToMP;               /*Install Com Func*/
  #endif

  clear_watch_dog();
  ini_pcb_queue();
  clear_watch_dog();
  run_pcb_queue(ProIdleQueue);                   /* Run Base Process*/
  clear_watch_dog();
  SetVector(0x08,(void far *)newThandler);
}

/*===========================================================================*/
//extern  void  far MimSIOInt(void);
/*------------------------------------*/
void  MainLoop()
{
  WORD pro4;
  WORD next;
  pro4=0;
  for(;;)
  {
//    MimSIOInt();
    CurRunTime++;
    run_pcb_msg();
    run_pcb_tcb();                    /*Deal Arrived Timer Queue*/

    if(CurTimeDate.ms10 != SysTimeDate.ms10)
    {
      CurTimeDate.ms10 = SysTimeDate.ms10;
      run_pcb_queue(Pro10msQueue);                 /*10ms Timer  Proc*/
    }
    if(CurTimeDate.ms100 != SysTimeDate.ms100)
    {
      CurTimeDate.ms100 = SysTimeDate.ms100;
      run_pcb_queue(Pro100msQueue);                 /*100ms Timer  Proc */
      pro4++;
      if(pro4==4)
      {
        pro4=0;
        run_pcb_queue(Pro400msQueue);               /*400ms Timer  Proc */
      }
    }
    if(CurTimeDate.second != SysTimeDate.second)
    {
      CurTimeDate.second = SysTimeDate.second;
      run_pcb_queue(Pro1000msQueue);                 /*1000ms Timer  Proc */
    }
  }
}

/*End Of main.c*/

