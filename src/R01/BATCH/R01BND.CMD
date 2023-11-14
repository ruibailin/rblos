#SAMPLE OF MAKEFILE
#AUTHOR:Rui Bailing
#DATE:  1997.08.20
#
MKFILE    = R01BND.CMD
BWCC      = E:\C600\BIN\CL              #Compiler Of .C File
MASM      = E:\MASM\MASM                #Compiler Of .ASM File
CLIB      = E:\C600\BINB\LIB            #Producer Of users Lib
LINK      = E:\LINK\BIN\LL86            #Producer Of users Omf
PROM      = E:\LINK\BIN\PROM86          #Producer Of users Bin

MODEL     = L                           #Large Model
FLOAT     = 0                           # No floating point
LIBS      = E:\LINK\SSILIB\ssiLce.lib   #Huge,Use Large Lib

WORK      = D:\TEST\MASM\WORK\                    #
R00       = D:\TEST\MASM\R00\                     #
R01       = D:\TEST\MASM\R01\                     #SET PATH OF MODULE
R02       = D:\TEST\MASM\R02\                     #
R06       = D:\TEST\MASM\R06\                     #
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
INCLUDE   = $(INCLUDE);$(R01)INCLUDE;
INCLUDE   = $(INCLUDE);..\INCLUDE\;

$(OBJECT)main.bin: $(OBJECT)main.omf $(MKFILE)
    $(PROM) $(OBJECT)main.omf to $(OBJECT)main.bin ad(0f0000h,0fffffh) bootstrap>5

INFILES   = $(R00)OBJECT\startup\
           ,$(OBJECT)R01BND.LIB\
           ,$(LIBS)
$(OBJECT)main.omf: $(OBJECT)R01BND.LIB main$(CPU86).cmd $(MKFILE)
    $(LINK) $(INFILES) @main$(CPU86).cmd>6

OBJS      =  $(OBJECT)t_pat.obj\
             $(OBJECT)test.obj
$(OBJECT)R01BND.LIB: $(OBJS) $(MKFILE)
     $(CLIB) $(OBJECT)R01BND.LIB -+$(OBJECT)r_rpc.OBJ,$(OBJECT)R01BND.LST,$(OBJECT)R01BND.LIB;
     $(CLIB) $(OBJECT)R01BND.LIB -+$(OBJECT)r_mem.OBJ,$(OBJECT)R01BND.LST,$(OBJECT)R01BND.LIB;
     $(CLIB) $(OBJECT)R01BND.LIB -+$(OBJECT)r_msg.OBJ,$(OBJECT)R01BND.LST,$(OBJECT)R01BND.LIB;
     $(CLIB) $(OBJECT)R01BND.LIB -+$(OBJECT)r_tcb.OBJ,$(OBJECT)R01BND.LST,$(OBJECT)R01BND.LIB;
     $(CLIB) $(OBJECT)R01BND.LIB -+$(OBJECT)r_pat.OBJ,$(OBJECT)R01BND.LST,$(OBJECT)R01BND.LIB;
     $(CLIB) $(OBJECT)R01BND.LIB -+$(OBJECT)r_pcb.OBJ,$(OBJECT)R01BND.LST,$(OBJECT)R01BND.LIB;
     $(CLIB) $(OBJECT)R01BND.LIB -+$(OBJECT)zxmain.OBJ,$(OBJECT)R01BND.LST,$(OBJECT)R01BND.LIB;
     $(CLIB) $(OBJECT)R01BND.LIB -+$(OBJECT)zxhard.OBJ,$(OBJECT)R01BND.LST,$(OBJECT)R01BND.LIB;
     $(CLIB) $(OBJECT)R01BND.LIB -+$(OBJECT)zxmml.OBJ,$(OBJECT)R01BND.LST,$(OBJECT)R01BND.LIB;
     $(CLIB) $(OBJECT)R01BND.LIB -+$(OBJECT)r_wdt.OBJ,$(OBJECT)R01BND.LST,$(OBJECT)R01BND.LIB;

     $(CLIB) $(OBJECT)R01BND.LIB -+$(OBJECT)t_pat.OBJ,$(OBJECT)R01BND.LST,$(OBJECT)R01BND.LIB;
     $(CLIB) $(OBJECT)R01BND.LIB -+$(OBJECT)test.OBJ,$(OBJECT)R01BND.LST,$(OBJECT)R01BND.LIB;

#The Follow Is For .C Or .CPP
CFLAGS    = $(CFLAGS) /Fc$(OBJECT)
CFLAGS    = $(CFLAGS)  /Fo$(OBJECT)
$(OBJECT)t_pat.obj: $(SOURCE)t_pat.c $(MKFILE)
    $(BWCC) $(CFLAGS) $(SOURCE)t_pat.c
$(OBJECT)test.obj: $(SOURCE)test.c $(MKFILE)
    $(BWCC) $(CFLAGS) $(SOURCE)test.c

