//DOS
#ifndef _rbltype_h
#define _rbltype_h

#define BYTE	unsigned char
#define WORD	unsigned int
#define DWORD	unsigned long
#define FAR	far
#define VFAR	void far
#define BFAR	unsigned char far
#define WFAR	unsigned int far
#define DFAR	unsigned long far


typedef struct{
    WORD  pno;
    WORD  unit;     
    WORD  module;   
} PID;

typedef struct{
    WORD  last;
    WORD  next;
    WORD  root;
} TAG;

#define R01                   0xf000
#define R01End                0xff00
#define Timer1Event           (WORD)(R01 + 0xe0)
#define Timer2Event           (WORD)(R01 + 0xe1)
#define Timer3Event           (WORD)(R01 + 0xe2)
#define Timer4Event           (WORD)(R01 + 0xe3)
#define Timer5Event           (WORD)(R01 + 0xe4)
#define Timer6Event           (WORD)(R01 + 0xe5)
#define Timer7Event           (WORD)(R01 + 0xe6)
#define Timer8Event           (WORD)(R01 + 0xe7)


#endif

