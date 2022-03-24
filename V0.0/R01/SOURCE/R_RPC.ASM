;	Static Name Aliases
;
        TITLE   ..\SOURCE\r_rpc.c
	.8087

PAT     STRUC
        task    DB      ?
        neme    DB      9   dup(?)
        steck   DW      ?
        entry   DD      ?
PAT     ENDS

R_RPC_TEXT      SEGMENT  WORD PUBLIC 'CODE'
R_RPC_TEXT      ENDS
_DATA   SEGMENT WORD    PUBLIC 'DATA'
_DATA   ENDS
CONST   SEGMENT WORD    PUBLIC 'CONST'
CONST	ENDS
_BSS    SEGMENT WORD    PUBLIC 'BSS'
_BSS	ENDS

DGROUP  GROUP   CONST, _BSS, _DATA
        ASSUME  DS: DGROUP,SS: DGROUP

        EXTRN _SysCurPno:WORD           ;near
        EXTRN _PATPool:BYTE             ;near

R_RPC_TEXT   SEGMENT
	ASSUME	CS: R_RPC_TEXT
R_RPC_TEXT   ENDS

CONST      SEGMENT
$T20000 DW SEG _SysCurPno
$T20001 DW SEG _PATPool
CONST      ENDS
R_RPC_TEXT   SEGMENT
        ASSUME  CS:R_RPC_TEXT
        public  _EXEPROC
		  public  _NEXTRET
_EXEPROC proc   far
		  push    bp
		  mov     bp,sp
		  push    si
		  push    di

		  mov     ax,TYPE PAT
		  mov     es,WORD PTR $T20000
		  imul    WORD ptr es:[_SysCurPno]
		  mov     bx,ax                           ;get offset of PATPool

		  mov     ax,sp                           ;save sp
		  mov     es,WORD PTR $T20001
                  mov     WORD ptr es:_PATPool[bx].steck,ax

		  push    word ptr[bp+08]
		  push    word ptr[bp+06]
		  call    DWORD ptr es:_PATPool[bx].entry
		  pop     ax
		  pop     ax

		  pop     di
		  pop     si
		  pop     bp
		  retf
_EXEPROC endp
_NEXTRET proc  far
                  mov     ax,TYPE PAT
                  mov     es,WORD PTR $T20000
                  imul    WORD ptr es:[_SysCurPno]
                  mov     bx,ax

                  mov     es,WORD PTR $T20001             ;get sp
                  mov     ax,WORD ptr es:_PATPool[bx].steck

                  sub     ax,8
                  mov     sp,ax
                  retf
_NEXTRET   endp
R_RPC_TEXT ends
        end

