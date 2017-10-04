################################################################################
# USAGE:
# make           .... build the program image
# make debug     .... build the program image and invoke gdb
# make flash     .... build an flash the application
# make doc       .... run doxygen - output will be in > doc
# make clean     .... remove intermediate and generated files

################################################################################
# define the name of the generated output file
#
TARGET        = main

################################################################################
# below only edit with care
#
BIN           = ./bin
SYS           = ./system
VENDOR        = Infineon
SRCDIR        = ./src
SRC           = $(wildcard src/*.c)
TOOLCHAIN     = arm-none-eabi
UC            = XMC4500
UC_ID         = 4503
CPU           = cortex-m4
FPU           = fpv4-sp-d16
FABI          = softfp  #soft, softfp, hard
LIBS          = -larm_cortexM4_mathL_2
LIBS         += -lxmclibcstubs
LIBS         += -lm
GDB_ARGS      = -ex "target remote :2331" 
GDB_ARGS     += -ex "monitor reset" 
GDB_ARGS     += -ex "load" 
GDB_ARGS     += -ex "monitor reset"
# uncomment the following line for semi-hosted debugging and comment the 
# RTT option below
#
# GDB_ARGS     += -ex "monitor SWO EnableTarget 16000000 0 1 0"
#
# set the Region of the RTT Block manually
GDB_ARGS     += -ex "monitor exec SetRTTAddr 0x20000C20"

CMSIS         = $(SYS)/CMSIS
CMSIS_INCDIR  = $(CMSIS)/Include
CMSIS_LIBDIR  = $(CMSIS)/Lib/GCC
INF_INCDIR    = $(CMSIS)/$(VENDOR)/Include
INF_LIBDIR    = $(CMSIS)/$(VENDOR)/Lib
XMC_INCDIR    = $(CMSIS)/$(VENDOR)/$(UC)_series/Include
XMC_LIBDIR    = $(CMSIS)/$(VENDOR)/$(UC)_series/Lib
XMC_SRCDIR    = $(CMSIS)/$(VENDOR)/$(UC)_series/Source
XMC_GCCDIR    = $(CMSIS)/$(VENDOR)/$(UC)_series/Source/GCC

INF_SRC       = $(INF_LIBDIR)/System_LibcStubs.c
XMC_SRC       = $(XMC_SRCDIR)/System_XMC4500.c
XMC_ASRC      = $(XMC_GCCDIR)/startup_XMC4500.asm
LINKER_FILE   = $(XMC_GCCDIR)/XMC4500.ld

LIBS_DIR      = -L$(SYS)
LIBS_DIR     += -L$(CMSIS_LIBDIR) 
LIBS_DIR     += -L$(INF_LIBDIR) 
LIBS_DIR     += -L$(XMC_LIBDIR)

INC_DIR = -I$(SRCDIR)
INC_DIR+= -I$(SYS)
INC_DIR+= -I$(CMSIS_INCDIR) 
INC_DIR+= -I$(INF_INCDIR) 
INC_DIR+= -I$(XMC_INCDIR)

AS   = $(TOOLCHAIN)-as
CC   = $(TOOLCHAIN)-gcc
CP   = $(TOOLCHAIN)-objcopy
OD   = $(TOOLCHAIN)-objdump
GDB  = $(TOOLCHAIN)-gdb
SIZE = $(TOOLCHAIN)-size

CFLAGS = -mthumb 
CFLAGS+= -mcpu=$(CPU) 
#CFLAGS+= -mfpu=$(FPU) 
#CFLAGS+= -mfloat-abi=$(FABI) 
CFLAGS+= -O0 
CFLAGS+= -ffunction-sections -fdata-sections -fsigned-char -fstack-usage
CFLAGS+= -MD -std=c99 -Wall -fms-extensions
CFLAGS+= -DUC_ID=$(UC_ID) -DARM_MATH_CM4
CFLAGS+= -g3 -fmessage-length=0 
AFLAGS = -x assembler-with-cpp 
LFLAGS = -nostartfiles $(LIBS_DIR) -Wl,--gc-sections -Wl,-Map=bin/$(TARGET).map
CPFLAGS = -Obinary
ODFLAGS = -S

OBJS = $(SRC:.c=.o)
OBJS+= $(INF_SRC:.c=.o)
OBJS+= $(XMC_SRC:.c=.o)
OBJS+= $(XMC_ASRC:.asm=.o)

#### Rules ####
all: $(OBJS) $(TARGET).elf $(TARGET)

%.o: %.c
	$(CC) -c $(CFLAGS) $(INC_DIR) $< -o $@

%.o: %.asm
	$(CC) -c $(CFLAGS) $(INC_DIR) $(AFLAGS) $< -o $@


$(TARGET).elf: $(OBJS)
	mkdir -p $(BIN)
	$(CC) -T $(LINKER_FILE) $(LFLAGS) $(CFLAGS) -o $(BIN)/$(TARGET).elf $(OBJS) $(LIBS)

$(TARGET): $(TARGET).elf
	$(CP) $(CPFLAGS) $(BIN)/$(TARGET).elf $(BIN)/$(TARGET).bin
	$(OD) $(ODFLAGS) $(BIN)/$(TARGET).elf > $(BIN)/$(TARGET).lst
	$(SIZE) $(BIN)/$(TARGET).elf

debug: $(TARGET)
	# comment the following line in Windows and launch JLinkGDBServer manually
	xterm -e "JLinkGDBServer -Device XMC4500-1024 -if SWD" &
	$(GDB) -q $(BIN)/$(TARGET).elf $(GDB_ARGS)

flash: $(TARGET)
	echo -e 'h\nloadbin bin/$(TARGET).bin,0xC000000\nr\ng\nq' | JLinkExe -Device XMC4500-1024 -if SWD
	
doc: $(TARGET)
	doxygen

clean:
	rm -f $(BIN)/* 
	rm -f $(SRCDIR)/*.o $(SRCDIR)/*.d $(SRCDIR)/*.su  $(SRCDIR)/*~ 
	rm -f $(SYS)/*.o $(SYS)/*.d $(SYS)/*.su $(SYS)/*~
	rm -f $(XMC_SRCDIR)/*.o $(XMC_SRCDIR)/*.d $(XMC_SRCDIR)/*.su $(XMC_SRCDIR)/*~
	rm -rf $(XMC_GCCDIR)/*.o $(XMC_GCCDIR)/*.d $(XMC_GCCDIR)/*.su $(XMC_GCCDIR)/*~
	rm -rf doc/html
