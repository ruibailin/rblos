#include "zxhard.h"
  #ifdef  __BORLANDC__
  #include <conio.h>
  void  Ini386(void);
  void  Ini386(void)
  {
	 _SetEXRegByte(DOS_TMRCON, 0x36);/* ;Set timer parameters.     */
	 _SetEXRegByte(DOS_TMR0, 0x9c);  /* ;Set the timer count (LO byte).*/
    _SetEXRegByte(DOS_TMR0, 0x2e);  /* ;Set the timer count (HI byte). */
  /*0x2e9c/1193180hz=10ms*/
  }
  #else
  void  Ini386(void);
  void  Ini386(void)
  {
    _SetEXRegByte(P3CFG, 0x00);     /*;Set the output location.*/
    _SetEXRegByte(TMRCFG, 0x00);    /*;Set input sources.       */
    _SetEXRegByte(DOS_TMRCON, 0x36);/* ;Set timer parameters.     */
    _SetEXRegByte(DOS_TMR0, 0xf4);  /* ;Set the timer count (LO byte).*/
    _SetEXRegByte(DOS_TMR0, 0x01);  /* ;Set the timer count (HI byte). */

    _SetEXRegByte(DOS_ICW1S, 0x11); /* Set slave triggering */
    _SetEXRegByte(DOS_ICW2S, 0x20); /* Set slave base interrupt type */
    _SetEXRegByte(DOS_ICW3S, 0x2);  /* Set slave cascade pins */
    _SetEXRegByte(DOS_ICW4S, 0x1);  /* Set slave IDs */

    _SetEXRegByte(DOS_ICW1M, 0x11); /* Set master triggering */
    _SetEXRegByte(DOS_ICW2M, 0x8);  /* Set master base interrupt type */
    _SetEXRegByte(DOS_ICW3M, 0x4);  /* Set master cascade pins */
    _SetEXRegByte(DOS_ICW4M, 0x1);  /* Set slave IDs in master */

    _SetEXRegByte(INTCFG, 0x0);     /* Set external interrupt pins */
    _SetEXRegByte(P3CFG, 0x0);      /* Set external interrupt pins */

    _SetEXRegByte(DOS_OCW1M, 0xFA); /* open interrupt mask,slave 8259 & timer */
    _SetEXRegByte(DOS_OCW1S, 0xFF); /* open interrupt mask */
  }
  #endif
