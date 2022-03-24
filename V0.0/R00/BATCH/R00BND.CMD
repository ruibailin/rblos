#SAMPLE OF MAKEFILE
#AUTHOR:Rui Beiling
#DATE:  1997.08.20
#
MKFILE    = R00BND.CMD
BWCC      = E:\C600\BIN\CL              #Compiler Of .C File
MASM      = E:\MASM\MASM                #Compiler Of .ASM File
CLIB      = E:\C600\BINB\LIB            #Producer Of users Lib
LINK      = E:\LINK\BIN\LL86            #Producer Of users Omf
PROM      = E:\LINK\BIN\PROM86          #Producer Of users Bin

MODEL     = L                           #Large Model
FLOAT     = 0                           # No floating point
LIBS      = E:\LINK\SSILIB\ssiLce.lib   #Huge,Use Large Lib

R00       = D:\MASM\R00\                #
R01       = D:\MASM\R01\                #SET PATH OF MODULE

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

OBJS      = $(OBJECT)startup.obj $(OBJECT)c_main.obj
INFILES   = $(OBJECT)startup\
           ,$(OBJECT)c_main\
           ,$(LIBS)

$(OBJECT)main.bin: $(OBJECT)main.omf $(MKFILE)
    $(PROM) $(OBJECT)main.omf to $(OBJECT)main.bin ad(0f0000h,0fffffh) bootstrap>5

$(OBJECT)main.omf: $(OBJS) main$(CPU86).cmd $(MKFILE)
    $(LINK) $(INFILES) @main$(CPU86).cmd >3

#The Follow Is For .ASM
$(OBJECT)startup.obj: $(SOURCE)startup.asm $(MKFILE)
    $(MASM) $(AFLAGS) $(SOURCE)startup,$(OBJECT)startup.obj,$(OBJECT)startup.lst

#The Follow Is For .C Or .CPP
CFLAGS    = $(CFLAGS)  /Fc$(OBJECT)
CFLAGS    = $(CFLAGS)  /Fo$(OBJECT)
$(OBJECT)c_main.obj: $(SOURCE)c_main.c $(MKFILE)
    $(BWCC) $(CFLAGS) $(SOURCE)c_main.c


