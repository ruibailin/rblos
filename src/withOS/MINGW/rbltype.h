//MINGW
#ifndef _rbltype_h
#define _rbltype_h

#define BYTE	unsigned char
#define WORD	unsigned short
#define DWORD	unsigned int
#define FAR	
#define VFAR	void
#define BFAR	unsigned char
#define WFAR	unsigned int
#define DFAR	unsigned long


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

