;	Static Name Aliases
;       TASM in large or huge mode because of far call
	TITLE   r_rpc.c
	.8087


R_RPC_TEXT      SEGMENT  WORD PUBLIC 'CODE'
R_RPC_TEXT      ENDS
_DATA   SEGMENT WORD    PUBLIC 'DATA'
_DATA   ENDS


R_RPC_TEXT   SEGMENT
	ASSUME	CS: R_RPC_TEXT
R_RPC_TEXT   ENDS

R_RPC_TEXT   SEGMENT
        ASSUME  CS:R_RPC_TEXT
        public  _get_sp
	public	_set_sp
_get_sp proc   far
		  mov     ax,sp
		  retf
_get_sp endp

_set_sp proc  far
		  sub     ax,4
                  mov     sp,ax
                  retf
_set_sp   endp
R_RPC_TEXT ends
        end

