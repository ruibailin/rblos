#include "zxj10.h"
typedef struct{
  WORD  LoWord;
  WORD  HiWord;
}DWORD;
typedef union{
  BYTE  far *pointer;
  DWORD      address;
}U_PTR;
static  WORD  RamSeg=0x0000;      /*ram start useable address*/
static  WORD  RomSeg=0xd000;      /*flash memory start useable address*/

extern  WORD  far GetSSSP(void);
BYTE  far *alloc_ram(WORD  len);
BYTE  far *alloc_ram(WORD  len)
{
  U_PTR   ptr;
  long    ll;
  if(RamSeg == 0x0000)
  RamSeg=GetSSSP();              /*Get Max Useable Segment*/

  ptr.address.HiWord=RamSeg;
  ptr.address.LoWord=0x0000;

  ll=(unsigned long)len+15;
  len=(WORD)(ll>>4);
  len += RamSeg;
  if(len < 0x4000)
  {
    RamSeg=len;
    return(ptr.pointer);
  }
  ptr.address.HiWord=0x0000;
  ptr.address.LoWord=0x0000;
  return(ptr.pointer);
}
BYTE  far *alloc_rom(WORD  len);
BYTE  far *alloc_rom(WORD  len)
{
  U_PTR   ptr;
  ptr.address.HiWord=0x0000;
  ptr.address.LoWord=0x0000;
  return(ptr.pointer);
}
/*End of r_mem.c*/
