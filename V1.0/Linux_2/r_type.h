//MINGW
#ifndef _r_type_h
#define _r_type_h

#define SIZEOF_CHAR		1
#define SIZEOF_SHORT	2
#define SIZEOF_INT		4
#define SIZEOF_LONG		8

#ifndef BYTE
typedef		unsigned char	BYTE;
#endif

#ifndef WORD
typedef		unsigned short	WORD;
#endif

#ifndef DWORD
#if SIZEOF_INT == 4
typedef		unsigned int	DWORD;
#else
typedef		unsigned long	DWORD;
#endif
#endif

#ifndef INT16
typedef   signed short       INT16;
#endif

#ifndef INT32
#if SIZEOF_INT == 4
typedef   signed int       INT32;
#else
typedef   signed long      INT32;
#endif
#endif

#ifndef	Bit8u
typedef unsigned char      Bit8u;
typedef   signed char      Bit8s;
#endif

#ifndef	Bit16u
typedef unsigned short     Bit16u;
typedef   signed short     Bit16s;
#endif

#ifndef	Bit32u
#if SIZEOF_INT == 4
typedef unsigned int       Bit32u;
typedef   signed int       Bit32s;
#else
typedef unsigned long       Bit32u;
typedef   signed long       Bit32s;
#endif
#endif

#endif

