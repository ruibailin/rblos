/* ZXJ10.H
   Copyright(c) 1993-1997. (ZTE)Shenzhen Zhongxing New Telecom Equip. Co. Ltd.
   Research Institute of Nanjing Zhongxing New Telecom.
   All rights reserved. */

#ifndef __ZXJ10_H
#define __ZXJ10_H

#if defined(_ARCHITECTURE_)
	#pragma noalign /* noalign for ic386 */
#elif defined(__BORLANDC__)
	#pragma option -a- /* noalign for Borland C */
#elif defined(_MSC_VER)
	#pragma pack(1) /* noalign for Microsoft C */
#elif defined(__WATCOMC__)
	#pragma pack(1) /* noalign for Watcom C */
#endif

  #define BYTE unsigned char
  #define WORD unsigned int
  #define WORD16 unsigned int
  #define WORD32 long
  #define UINT16 unsigned int
  #define UINT32 long
  #define LPSTR unsigned char far *
  #define BOOL  unsigned char
  #define OFFSET(ptr) *(WORD *)((LPSTR *)&ptr)
  #define SEGMENT(ptr) *(WORD *)((LPSTR *)&ptr+2)

  #define TRUE    (BOOL)1
  #define FALSE   (BOOL)0

/* Type declaration used in ZXJ10B  PP system */

typedef BYTE    SDN[20];
typedef BYTE    LSDN[32];

typedef struct {
    BYTE    hw;     /* 模块内HW线的序号{1,..,2560} */
    BYTE    ts;     /* 2Mb/s HW线的时隙号{0,1,..,31} */
} TLN;

typedef struct {
    BYTE    index;  /* SLN所属子单元内的电路序号 */
    BYTE    sunit;  /* SLN所属子单元号 */
    BYTE    unit;   /* SLN所属单元号 */
} SLN;

/*  呼叫用户逻辑号 */
typedef struct{
    BYTE  index;
    BYTE  sunit;
  }ppSLN;

typedef struct {
    ppSLN     sln;    /* SLN */
    WORD      isdn;
} CSN;

typedef struct{
    WORD  pno;      /*  */
    BYTE  unit;     /* SLN所属单元号 */
    BYTE  module;   /* SLN所属模块号 */
} PID;

typedef struct{
    WORD  pno;      /*  */
    BYTE  unit;     /* SLN所属单元号 */
    BYTE  module;   /* SLN所属模块号 */
    BYTE  office;   /* bureau number */
} MPPID;

typedef struct{
    WORD  last;
    WORD  next;
    WORD  root;
} TAG;

#endif
