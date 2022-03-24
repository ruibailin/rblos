;
; Copyright (c) 1990-1992, Systems & Software, Inc. All rights reserved.
;
IFDEF		__S__
   LPROG    equ   0
   LDATA    equ   0
ELSEIFDEF	__C__
   LPROG    equ   0
   LDATA    equ   1
ELSEIFDEF	__M__
   LPROG    equ   1
   LDATA    equ   0
ELSEIFDEF	__L__
   LPROG    equ   1
   LDATA    equ   1
ELSEIFDEF	__H__
   LPROG    equ   1
   LDATA    equ   1
ELSE	   ; no model defined , default as L model
   LPROG    equ   1
   LDATA    equ   1
ENDIF	; IFDEF

;IF LPROG
;   DIST  equ   FAR
;ELSE
;   DIST  equ   NEAR
;ENDIF
;CPU86 EQU 0
;FLOAT EQU 0
;STACK_SIZE EQU 4096
