;; ZXJ10.H
;; Copyright(c) 1993-1997. (ZTE)Shenzhen Zhongxing New Telecom Equip. Co. Ltd.
;; Research Institute of Nanjing Zhongxing New Telecom.
;; All rights reserved.

;FOR EX386 INITIAL ONLY
;INCLUDE MACRO
;   _SetEXRegWord
;   _SetEXRegByte
;   _LightRunLed
;   _DimRunLed
;   _TestSegRam
;   _InitEX386Reg

;________________________________________
;________________________________________
_SetEXRegWord MACRO reg,val
  MOV   DX,reg
  MOV   AX,val
  out   DX,AX
ENDM
;________________________________________
;________________________________________
_SetEXRegByte MACRO reg,val
  MOV   DX,reg
  MOV   AL,val
  OUT   DX,AL
ENDM
;________________________________________
;________________________________________
_Delay10ms  MACRO
  MOV   CX,0FFFFH       ;3
  LOOP  $               ;2
ENDM
;________________________________________
; GREEN_led Off ;Clear WDT
;________________________________________
_DimRunLed    MACRO
  MOV   DX, P3LTC
  IN    AX, DX
  OR    AX, 10000010B
  OUT   DX, AX
ENDM
;________________________________________
; GREEN_led ON;Clear WDT
;________________________________________
_LightRunLed    MACRO
  MOV   DX, P3LTC       ; GREEN_led Off,RED_LED On
  IN    AX, DX
  AND   AX, 01111101B
  OUT   DX, AX
ENDM
;________________________________________
; Red_Led Off;Clear WDT
;________________________________________
_DimWarnLed    MACRO
  MOV   DX, P3LTC       ; GREEN_led Off,RED_LED On
  IN    AX, DX
  OR    AX, 01000010B
  OUT   DX, AX
ENDM
;________________________________________
; Red_led ON;Clear WDT
;________________________________________
_LightWarnLed    MACRO
  MOV   DX, P3LTC       ; GREEN_led Off,RED_LED On
  IN    AX, DX
  AND   AX, 10111101B
  OUT   DX, AX
ENDM
;________________________________________
;Test 64K RAM (a segment),
;dseg:segment,val:value writed into ram
;________________________________________
_TestSegRam  MACRO dseg,val
  CLD
  MOV   AX,dseg
  MOV   ES,AX
  MOV   DI,0
  MOV   CX,8000H
  MOV   AX,val
  REP   STOSW

  CLD
  MOV   AX,dseg
  MOV   ES,AX
  MOV   DI,0
  MOV   AX,val
  MOV   CX,8000H
  REPE  SCASW
ENDM

;________________________________________
;________________________________________
_InitEX386Reg MACRO

        IN      AL,92H          ;Clear Port 92 Reset
        AND     AL,0FEH
        OR      AL,02H
        OUT     92H,AL


        MOV     AX, 0080H       ; open expanded I/O space
        XCHG    AL, AH          ;DOS ENHANCED MODE/ LOW
        OUT     REMAPCFGH, AL
        XCHG    AL, AH
        OUT     REMAPCFGL, AL
        OUT     REMAPCFGL, AX
  _SetEXRegByte REMAPCFGL, 00H  ;Map peripherals
  
  
  _SetEXRegByte WDTSTATUS, 01H    ;Disable the WDT.


;Initialize I/O Port 1 for input:
  _SetEXRegByte P1CFG, 00H
  _SetEXRegByte P1DIR, 0FFH
  _SetEXRegByte P1LTC, 0FFH

;Initialize I/O Port 3 for Output:
  _SetEXRegByte P3CFG, 00H
  _SetEXRegByte P3DIR, 00H
  _SetEXRegByte P3LTC, 40H



;Initialize I/O Port 2 for:
;  PIN 0 = CS0# Peripheral Pin
;  PIN 1 = CS1# Peripheral Pin
;  PIN 2 = CS2# Peripheral Pin
;  PIN 3 = CS3# Peripheral Pin
;  PIN 4 = CS4# Peripheral Pin
;  PIN 5 = RXD0 Peripheral Pin
;  PIN 6 = TXD0 Peripheral Pin
;  PIN 7 = Output
  _SetEXRegByte P2CFG, 07FH
  _SetEXRegByte P2DIR, 00H
  _SetEXRegByte P2LTC, 080H

; Initialize Peripheral Pin Configurations
; SET CS5# CS6# CTS1# DACK1# SRXCLK SSIOTX
  _SetEXRegByte PINCFG, 1FH     ;08H


;Initialize Chip Select Unit for:
;  UCS:   Start address is 0E0000H.
;         Region size is 128 Kbytes.
;         2 wait states.
;         Upper chip select is Enabled.
;         8 bit data bus size in memory space.
;         External bus ready is Disabled.
;         SMM region is accessable during SMI access and memory access.
;  CS0:   Start address is 0C0000H.
;         Region size is 128 Kbytes.
;         2 wait states.
;         Chip select 0 is Enabled.
;         Chip select 0 is Enabled.
;         16 bit data bus size in memory space.
;         External bus ready is Disabled.
;         SMM region is accessable during SMI access and memory access.
;  CS1:   Start address is 070000H.
;         Region size is 2 Kbytes.
;         0 wait states.
;         Chip select 1 is Enabled.
;         8 bit data bus size in memory space.
;         External bus ready is Disabled.
;         SMM region is accessable during SMI access and memory access.
;  CS2:   Start address is 040000H.
;         Region size is 2 Kbytes.
;         4 wait states.
;         Chip select 2 is Enabled.
;         8 bit data bus size in memory space.
;         External bus ready is Disabled.
;         SMM region is accessable during SMI access and memory access.
;  CS3:   Start address is 060000H.
;         Region size is 2 Kbytes.
;         4 wait states.
;         Chip select 3 is Enabled.
;         8 bit data bus size in memory space.
;         External bus ready is Disabled.
;         SMM region is accessable during SMI access and memory access.
;  CS4:  Start address is 050000H.
;         Region size is 4 Kbytes.
;         0 wait states.
;         Chip select 4 is Enabled.
;         8 bit data bus size in memory space.
;         External bus ready is Enabled.
;         SMM region is accessable during SMI access and memory access.
;  CS5:   Start address is 00H.
;         Region size is 2 bytes.
;         0 wait states.
;         Chip select 5 is Disabled.
;         8 bit data bus size in I/O space.
;         External bus ready is Disabled.
;         SMM region is accessable during SMI access and memory access.
;  CS6:   Start address is 00H.
;         Region size is 256 Kbytes.
;         2 wait states.
;         Chip select 6 is Enabled.
;         16 bit data bus size in memory space.
;         External bus ready is Disabled.
;         SMM region is accessable during SMI access and memory access.


  _SetEXRegWord UCSADL, 0502H     ;Configure the upper chip select
  _SetEXRegWord UCSADH, 0EH        ;EPROM   0e0000-0fffffh
  _SetEXRegWord UCSMSKL, 0FC01H
  _SetEXRegWord UCSMSKH, 01H

  _SetEXRegWord CS0ADL, 0702H         ;Configure chip select 0
  _SetEXRegWord CS0ADH, 0CH           ;flash 0c0000h-0dffffh   128k
  _SetEXRegWord CS0MSKL, 0FC01H
  _SetEXRegWord CS0MSKH, 01H


  _SetEXRegWord CS6ADL, 0700H         ;Configure chip select 6
  _SetEXRegWord CS6ADH, 00H
  _SetEXRegWord CS6MSKL, 0FC01H
  _SetEXRegWord CS6MSKH, 03H


;Initialize the Clock and Power Management Unit for:
;  Clock frequency of 50.00000 MHz.
;  Prescaled clock output of 12.50000 MHz.
;  Normal Halt Instructions.
                                    
  _SetEXRegByte PWRCON, 00H
  _SetEXRegWord CLKPRS, 01F2H    ;PSCLK=50M\2\500=50KHZ

ENDM

_NULLMACRO     MACRO
  _SetEXRegWord CS1ADL, 0500H         ;Configure chip select 1
  _SetEXRegWord CS1ADH, 07H            ;BS    070000h       2k
  _SetEXRegWord CS1MSKL, 0401H
  _SetEXRegWord CS1MSKH, 00H

  _SetEXRegWord CS2ADL, 0506H         ;Configure chip select 2
  _SetEXRegWord CS2ADH, 04H            ;HDLC   040000h      2k
  _SetEXRegWord CS2MSKL, 0401H
  _SetEXRegWord CS2MSKH, 00H

  _SetEXRegWord CS3ADL, 0506H         ;Configure chip select 3
  _SetEXRegWord CS3ADH, 06H            ;LAY     060000h     2k
  _SetEXRegWord CS3MSKL, 0401H
  _SetEXRegWord CS3MSKH, 00H

  _SetEXRegWord CS4ADL, 0580H         ;Configure chip select 4
  _SetEXRegWord CS4ADH, 05H            ;898X     050000h     4k
  _SetEXRegWord CS4MSKL, 0C01H
  _SetEXRegWord CS4MSKH, 00H

  _SetEXRegWord CS5ADL, 0400H         ;Configure chip select 5
  _SetEXRegWord CS5ADH, 00H
  _SetEXRegWord CS5MSKL, 0400H
  _SetEXRegWord CS5MSKH, 00H
ENDM

