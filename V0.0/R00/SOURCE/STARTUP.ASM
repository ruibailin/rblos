                NAME    MSC_START_UP_CODE
                PUBLIC  __acrtused
__acrtused      EQU     1
       
                INCLUDE STARTUP.INC
                INCLUDE 386EX.INC
                INCLUDE initial.INC

BEGFDATA        SEGMENT PARA PUBLIC 'FAR_DATA_BEG'
                PUBLIC  _bfdata
_bfdata         LABEL   BYTE
BEGFDATA        ENDS
FAR_DATA_START  SEGMENT PARA PUBLIC 'FAR_DATA'
FAR_DATA_START  ENDS
EMULATOR_DATA   SEGMENT PARA PUBLIC 'FAR_DATA'
EMULATOR_DATA   ENDS
ENDFDATA        SEGMENT PARA PUBLIC 'FAR_DATA_END'
                PUBLIC  _efdata
_efdata         LABEL   BYTE
ENDFDATA        ENDS
BEGFBSS         SEGMENT PARA PUBLIC 'FAR_BSS_BEG'
                PUBLIC  _bfbss
_bfbss          LABEL   BYTE
BEGFBSS         ENDS
FAR_BSS_START   SEGMENT PARA PUBLIC 'FAR_BSS'
FAR_BSS_START   ENDS
ENDFBSS         SEGMENT PARA PUBLIC 'FAR_BSS_END'
                PUBLIC  _efbss
_efbss          LABEL   BYTE
ENDFBSS         ENDS
BEGHBSS         SEGMENT PARA PUBLIC 'HUGE_BSS_BEG'
                PUBLIC  _bhbss
_bhbss          LABEL   BYTE
BEGHBSS         ENDS
HUGE_BSS_START  SEGMENT PARA PUBLIC 'HUGE_BSS'
HUGE_BSS_START  ENDS
ENDHBSS         SEGMENT PARA PUBLIC 'HUGE_BSS_END'
                PUBLIC  _ehbss
_ehbss          LABEL   BYTE
ENDHBSS         ENDS

DGROUP          GROUP   BDATA,_DATA,PSP,CDATA
DGROUP          GROUP   XIFCB,XIFU,XIFL,XIFM,XIFCE,XIFB,XIF,XIFE
DGROUP          GROUP   XIB,XI,XIE
DGROUP          GROUP   CONST,HDR,MSG,PAD,EPAD,ENDDATA,_BSS,ENDBSS,STACK

BDATA           SEGMENT PARA PUBLIC 'DATA_BEG'
                PUBLIC  _bdata
_bdata          LABEL   BYTE
BDATA           ENDS
_DATA           SEGMENT WORD PUBLIC 'DATA'
_DATA           ENDS
PSP             SEGMENT PARA PUBLIC 'DATA'
PSP ENDS
CDATA           SEGMENT WORD COMMON 'DATA'
CDATA           ENDS

XIFCB           SEGMENT WORD PUBLIC 'DATA'
xifcbegin       LABEL   BYTE
XIFCB           ENDS
XIFU            SEGMENT WORD PUBLIC 'DATA'
XIFU            ENDS
XIFL            SEGMENT WORD PUBLIC 'DATA'
XIFL            ENDS
XIFM            SEGMENT WORD PUBLIC 'DATA'
XIFM            ENDS
XIFCE           SEGMENT WORD PUBLIC 'DATA'
    xifcend     LABEL   BYTE
XIFCE           ENDS
XIFB            SEGMENT WORD PUBLIC 'DATA'
xifbegin        LABEL   BYTE
XIFB            ENDS
XIF             SEGMENT WORD PUBLIC 'DATA'
XIF             ENDS
XIFE            SEGMENT WORD PUBLIC 'DATA'
xifend          LABEL   BYTE
XIFE            ENDS

XIB             SEGMENT WORD PUBLIC 'DATA'
xibegin         LABEL   BYTE
XIB             ENDS
XI              SEGMENT WORD PUBLIC 'DATA'
XI              ENDS
XIE             SEGMENT WORD PUBLIC 'DATA'
xiend           LABEL   BYTE
XIE             ENDS

CONST           SEGMENT WORD PUBLIC 'CONST'
CONST           ENDS
HDR             SEGMENT BYTE PUBLIC 'MSG'
HDR             ENDS
MSG             SEGMENT BYTE PUBLIC 'MSG'
MSG             ENDS
PAD             SEGMENT BYTE COMMON 'MSG'
PAD             ENDS
EPAD            SEGMENT BYTE COMMON 'MSG'
EPAD            ENDS

$$SYMBOLS       SEGMENT  BYTE PUBLIC 'DEBSYM'
$$SYMBOLS	ENDS
$$TYPES SEGMENT  BYTE  PUBLIC 'DEBTYP'
$$TYPES	ENDS

ENDDATA         SEGMENT PARA PUBLIC 'DATA_END'
                PUBLIC  _edata
_edata          LABEL   BYTE
                PUBLIC  __edata
__edata         LABEL   BYTE
ENDDATA         ENDS
_BSS            SEGMENT WORD PUBLIC 'BSS'
_BSS            ENDS
ENDBSS          SEGMENT WORD PUBLIC 'BSS_END'
                PUBLIC  _end
_end            LABEL   BYTE
                PUBLIC  __end
__end           LABEL   BYTE
ENDBSS          ENDS

STACK           SEGMENT PARA STACK 'STACK'
                DB      STACK_SIZE DUP (?)
stack_top       LABEL   WORD
STACK           ENDS

;------------------------------------------
                EXTRN   _main:FAR
_TEXT           SEGMENT PARA PUBLIC 'CODE'
                ASSUME  CS:_TEXT
                ASSUME  DS:DGROUP, SS:DGROUP
                PUBLIC  START_
                PUBLIC  _GetSSSP
                PUBLIC  _GetCS
START_:
                PUBLIC  _START_
_start_         proc    far
                CLI

                MOV     CX,0FFFFH
                NOP
                NOP
                NOP
                LOOP    $-3

                JMP     _Init386All
_EndInit386:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Initialize  DATA AREA
;
                CLD
                MOV     AX,SEG _bdata
                MOV     ES,AX            ; Destination ES:[DI]
                MOV     DI,0             ; Start of initialized variable area in RAM
                MOV     AX,SEG _brdata   ; Source DS:[SI]
                INC     AX               ; Skip the 16-byte string 'Rom Data Begin  '
                MOV     DS,AX            ; Start of initializer storage in ROM
                MOV     SI,0
                MOV     AX,OFFSET DGROUP:_edata ; Transfer counter
                MOV     CX,AX
                REP     MOVSB

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Go TO  MAIN
;
                MOV     AX,DGROUP
                MOV     DS,AX
                ASSUME  DS:DGROUP
                MOV     SS,AX
                MOV     SP,OFFSET DGROUP:stack_top
                ASSUME  SS:DGROUP
                CLI
                CALL    _main
                HLT

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_Init386All:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Inititialize 386EX
;
                _InitEX386Reg
                NOP
                NOP
                NOP
                MOV     BX,0AH
LoopGreenLed:
                _LightRunLed
                _Delay10ms
                _DimRunLed
                _Delay10ms
                DEC     BX
                MOV     AX,BX
                JNZ     LoopGreenLed
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;TEST   RAM
;
                _TestSegRam     0000H,5555H
                JZ      $+5                     ;Ram Is Good
                JMP     RamIsError
                _TestSegRam     0000H,0AAAAH
                JZ      $+5                     ;Ram Is Good
                JMP     RamIsError
                _TestSegRam     1000H,5555H
                JZ      $+5                     ;Ram Is Good
                JMP     RamIsError
                _TestSegRam     1000H,0AAAAH
                JZ      $+5                     ;Ram Is Good
                JMP     RamIsError
                _TestSegRam     2000H,5555H
                JZ      $+5                     ;Ram Is Good
                JMP     RamIsError
                _TestSegRam     2000H,0AAAAH
                JZ      $+5                     ;Ram Is Good
                JMP     RamIsError
                _TestSegRam     3000H,5555H
                JZ      $+5                     ;Ram Is Good
                JMP     RamIsError
                _TestSegRam     3000H,0AAAAH
                JZ      $+5                     ;Ram Is Good
                JMP     RamIsError
RamIsGood:
                NOP
                NOP
                NOP
                _TestSegRam     0000H,00H       ;Clear To 0
                _TestSegRam     1000H,00H
                _TestSegRam     2000H,00H
                _TestSegRam     3000H,00H
                JMP     _EndInit386
RamIsError:
                NOP
                NOP
                NOP
                MOV     BX,0AH
LoopRedLed:
                _LightWarnLed
                _Delay10ms
                _DimWarnLed
                _Delay10ms
                DEC     BX
                MOV     AX,BX
                JNZ     LoopRedLed
                NOP
                NOP
                NOP
                HLT
_start_         endp

;----------------------------------
_GetSSSP        proc    far
                MOV     AX,OFFSET DGROUP:stack_top
                SHR     AX,1
                SHR     AX,1
                SHR     AX,1
                SHR     AX,1
                MOV     BX,AX
                MOV     AX,SS
                ADD     AX,BX
                ADD     AX,01H
                RETF
_GetSSSP        endp
;----------------------------------
_GetCS          proc    far
                PUSH    CS
                POP     AX
                AND     AX,0f000h
                RETF
_GetCS          endp
;----------------------------------

_TEXT           ENDS


EMULATOR_TEXT   SEGMENT PARA PUBLIC 'CODE'
EMULATOR_TEXT   ENDS
SSI_ROMDATA     SEGMENT PARA PUBLIC 'SSI_ROMINIT'
                DB      'Rom Data Begin  '
                PUBLIC  _etext
_etext          LABEL   BYTE
                PUBLIC  _brdata
_brdata         LABEL   BYTE
SSI_ROMDATA     ENDS
                END     START_
                END
