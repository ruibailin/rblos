#SAMPLE OF MAKEFILE
#AUTHOR:Rui Bailing
#DATE:  1997.08.20
#
MKFILE    = R01ICC.CMD
BWCC      = E:\c600\BIN\CL              #Compiler Of .C File
MASM      = e:\MASM\MASM                #Compiler Of .ASM File
CLIB      = E:\c600\BINB\LIB            #Producer Of users Lib
LINK      = e:\LINK\BIN\LL86            #Producer Of users Omf
PROM      = e:\LINK\BIN\PROM86          #Producer Of users Bin

MODEL     = L                           #Medium Model
FLOAT     = 0                           # No floating point
LIBS      = e:\LINK\SSLIB\ssi$(MODEL)ce.lib

WORK      = D:\TEST\MASM\WORK\                    #
R00       = D:\TEST\MASM\R00\                     #
R01       = D:\TEST\MASM\R01\                     #SET PATH OF MODULE
R06       = D:\TEST\MASM\R06\                     #
B00       = D:\TEST\MASM\B00\                     #
B01       = D:\TEST\MASM\B01\                     #
B02       = D:\TEST\MASM\B02\                     #

#The Follow Option Is For C Or C++ Program
CFLAGS    = /A$(MODEL) /Zi /Zp /Gs /c /Od
#The Follow Option Is For ASM Program
CPU86     = 1                           #Select 8086
STACKSIZE = 8192                        #Set deepth of stack
AFLAGS    = /MX /Zi    /D__$(MODEL)__  /DSTACK_SIZE=$(STACKSIZE)
AFLAGS    = $(AFLAGS) /DCPU86=$(CPU86) /DFLOAT=$(FLOAT)

SOURCE    = ..\SOURCE\                  # "#" Must Be Hear
OBJECT    = ..\OBJECT\                  #
#SET DOS ENVIRONMENT OF INCLUDE ITEM
INCLUDE   = E:\C600\INCLUDE;
INCLUDE   = $(INCLUDE);..\INCLUDE\;
INCLUDE   = $(INCLUDE);$(B00)INCLUDE\;
INCLUDE   = $(INCLUDE);$(B01)INCLUDE\;

OBJS      = $(OBJECT)r_rpc.obj\
            $(OBJECT)r_mem.obj $(OBJECT)r_msg.obj\
            $(OBJECT)r_tcb.obj\
            $(OBJECT)r_pcb.obj  $(OBJECT)r_pat.obj\
            $(OBJECT)zxmain.obj $(OBJECT)zxhard.obj\
            $(OBJECT)zxmml.obj  $(OBJECT)r_wdt.obj
$(OBJECT)R01ICC.LIB: $(OBJS) $(MKFILE)
     $(CLIB) $(OBJECT)R01ICC.LIB -+$(OBJECT)r_rpc.OBJ,$(OBJECT)R01ICC.LST,$(OBJECT)R01ICC.LIB;
     $(CLIB) $(OBJECT)R01ICC.LIB -+$(OBJECT)r_mem.OBJ,$(OBJECT)R01ICC.LST,$(OBJECT)R01ICC.LIB;
     $(CLIB) $(OBJECT)R01ICC.LIB -+$(OBJECT)r_msg.OBJ,$(OBJECT)R01ICC.LST,$(OBJECT)R01ICC.LIB;
     $(CLIB) $(OBJECT)R01ICC.LIB -+$(OBJECT)r_tcb.OBJ,$(OBJECT)R01ICC.LST,$(OBJECT)R01ICC.LIB;
     $(CLIB) $(OBJECT)R01ICC.LIB -+$(OBJECT)r_pat.OBJ,$(OBJECT)R01ICC.LST,$(OBJECT)R01ICC.LIB;
     $(CLIB) $(OBJECT)R01ICC.LIB -+$(OBJECT)r_pcb.OBJ,$(OBJECT)R01ICC.LST,$(OBJECT)R01ICC.LIB;
     $(CLIB) $(OBJECT)R01ICC.LIB -+$(OBJECT)zxmain.OBJ,$(OBJECT)R01ICC.LST,$(OBJECT)R01ICC.LIB;
     $(CLIB) $(OBJECT)R01ICC.LIB -+$(OBJECT)zxhard.OBJ,$(OBJECT)R01ICC.LST,$(OBJECT)R01ICC.LIB;
     $(CLIB) $(OBJECT)R01ICC.LIB -+$(OBJECT)zxmml.OBJ,$(OBJECT)R01ICC.LST,$(OBJECT)R01ICC.LIB;
     $(CLIB) $(OBJECT)R01ICC.LIB -+$(OBJECT)r_wdt.OBJ,$(OBJECT)R01ICC.LST,$(OBJECT)R01ICC.LIB;

#The Follow Is For .ASM
#$(OBJECT)r_rpc.obj: $(SOURCE)r_rpc.asm $(MKFILE)
#    $(MASM) $(AFLAGS) $(SOURCE)r_rpc,$(OBJECT)r_rpc.obj,$(OBJECT)r_rpc.lst;

#The Follow Is For .C Or .CPP
CFLAGS    = $(CFLAGS) /Fc$(OBJECT)              #Produce Assembler File
CFLAGS    = $(CFLAGS) /Fo$(OBJECT)              #Object Files In ..\OBJECT\
$(OBJECT)r_msg.obj: $(SOURCE)r_msg.c $(MKFILE)
    $(BWCC) $(CFLAGS) $(SOURCE)r_msg.c
$(OBJECT)r_mem.obj: $(SOURCE)r_mem.c $(MKFILE)
    $(BWCC) $(CFLAGS) $(SOURCE)r_mem.c
$(OBJECT)r_tcb.obj: $(SOURCE)r_tcb.c $(MKFILE)
    $(BWCC) $(CFLAGS) $(SOURCE)r_tcb.c
$(OBJECT)r_pat.obj: $(SOURCE)r_pat.c $(MKFILE)
    $(BWCC) $(CFLAGS) $(SOURCE)r_pat.c
$(OBJECT)r_pcb.obj: $(SOURCE)r_pcb.c $(MKFILE)
    $(BWCC) $(CFLAGS) $(SOURCE)r_pcb.c
$(OBJECT)zxmain.obj: $(SOURCE)zxmain.c $(MKFILE)
    $(BWCC) $(CFLAGS) $(SOURCE)zxmain.c
$(OBJECT)zxhard.obj: $(SOURCE)zxhard.c $(MKFILE)
    $(BWCC) $(CFLAGS) $(SOURCE)zxhard.c
$(OBJECT)zxmml.obj: $(SOURCE)zxmml.c $(MKFILE)
    $(BWCC) $(CFLAGS) $(SOURCE)zxmml.c
$(OBJECT)r_wdt.obj: $(SOURCE)r_wdt.c $(MKFILE)
    $(BWCC) $(CFLAGS) $(SOURCE)r_wdt.c

