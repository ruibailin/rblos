#include "zxj10.h"
#include "r_pat.h"

extern void  far TestPro(BYTE far *ptr);
extern void  far Test1Pro(BYTE far *ptr);
extern void  far Test2Pro(BYTE far *ptr);
extern void  far ScanT(BYTE far *ptr);
/*------------------------------------*/
extern void far R01MMLMgt(BYTE far *);
extern void far WatchDog(BYTE far *);
/*------------------------------------*/
extern void far NULLPro(BYTE far *in);
/*------------------------------------*/
PAT PATPool[64]={
/*       task       name          stack       entry  */
/*000*/  0,        "NULLPro",     0,          &NULLPro,
/*001*/  0,        "NULLPro",     0,          &NULLPro,
/*002*/  0,        "R03Mgt",      0,          &R01MMLMgt,
/*003*/  0,        "NULLPro",     0,          &NULLPro,
/*004*/  0,        "NULLPro",     0,          &NULLPro,
/*005*/  0,        "NULLPro",     0,          &NULLPro,
/*006*/  0,        "NULLPro",     0,          &NULLPro,
/*007*/  0,        "NULLPro",     0,          &NULLPro,
/*008*/  0,        "NULLPro",     0,          &NULLPro,
/*009*/  0,        "NULLPro",     0,          &NULLPro,

/*010*/  1,        "NULLPro",     0,          &ScanT,
/*011*/  0,        "NULLPro",     0,          &TestPro,
/*012*/  0,        "NULLPro",     0,          &Test1Pro,
/*013*/  0,        "NULLPro",     0,          &Test2Pro,
/*014*/  0,        "NULLPro",     0,          &NULLPro,
/*015*/  0,        "NULLPro",     0,          &NULLPro,
/*016*/  0,        "NULLPro",     0,          &NULLPro,
/*017*/  0,        "NULLPro",     0,          &NULLPro,
/*018*/  0,        "NULLPro",     0,          &NULLPro,
/*019*/  0,        "NULLPro",     0,          &NULLPro,

/*020*/  0,        "WDT    ",     0,          &WatchDog,
/*021*/  0,        "NULLPro",     0,          &NULLPro,
/*022*/  0,        "NULLPro",     0,          &NULLPro,
/*023*/  0,        "NULLPro",     0,          &NULLPro,
/*024*/  0,        "NULLPro",     0,          &NULLPro,
/*025*/  0,        "NULLPro",     0,          &NULLPro,
/*026*/  0,        "NULLPro",     0,          &NULLPro,
/*027*/  0,        "NULLPro",     0,          &NULLPro,
/*028*/  0,        "NULLPro",     0,          &NULLPro,
/*029*/  0,        "NULLPro",     0,          &NULLPro,

/*030*/  0,        "NULLPro",     0,          &NULLPro,
/*031*/  0,        "NULLPro",     0,          &NULLPro,
          /*Follow Is MP Process*/
/*032*/  0,        "NULLPro",     0,          &NULLPro,
/*033*/  0,        "NULLPro",     0,          &NULLPro,
/*034*/  0,        "NULLPro",     0,          &NULLPro,
/*035*/  0,        "NULLPro",     0,          &NULLPro,
/*036*/  0,        "NULLPro",     0,          &NULLPro,
/*037*/  0,        "NULLPro",     0,          &NULLPro,
/*038*/  0,        "NULLPro",     0,          &NULLPro,
/*039*/  0,        "NULLPro",     0,          &NULLPro,

/*040*/  0,        "NULLPro",     0,          &NULLPro,
/*041*/  0,        "NULLPro",     0,          &NULLPro,
/*042*/  0,        "NULLPro",     0,          &NULLPro,
/*043*/  0,        "NULLPro",     0,          &NULLPro,
/*044*/  0,        "NULLPro",     0,          &NULLPro,
/*045*/  0,        "NULLPro",     0,          &NULLPro,
/*046*/  0,        "NULLPro",     0,          &NULLPro,
/*047*/  0,        "NULLPro",     0,          &NULLPro,
/*048*/  0,        "NULLPro",     0,          &NULLPro,
/*049*/  0,        "NULLPro",     0,          &NULLPro,

/*050*/  0,        "NULLPro",     0,          &NULLPro,
/*051*/  0,        "NULLPro",     0,          &NULLPro,
/*052*/  0,        "NULLPro",     0,          &NULLPro,
/*053*/  0,        "NULLPro",     0,          &NULLPro,
/*054*/  0,        "NULLPro",     0,          &NULLPro,
/*055*/  0,        "NULLPro",     0,          &NULLPro,
/*056*/  0,        "NULLPro",     0,          &NULLPro,
/*057*/  0,        "NULLPro",     0,          &NULLPro,
/*058*/  0,        "NULLPro",     0,          &NULLPro,
/*059*/  0,        "NULLPro",     0,          &NULLPro,

/*060*/  0,        "NULLPro",     0,          &NULLPro,
/*061*/  0,        "NULLPro",     0,          &NULLPro,
/*062*/  0,        "NULLPro",     0,          &NULLPro,
/*063*/  0,        "NULLPro",     0,          &NULLPro,
};
/*End Of r_pat.c*/
