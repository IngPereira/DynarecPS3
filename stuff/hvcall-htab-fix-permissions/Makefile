#   SCE CONFIDENTIAL                                      
#   PlayStation(R)3 Programmer Tool Runtime Library 370.001
#   Copyright (C) 2007 Sony Computer Entertainment Inc.   
#   All Rights Reserved.                                  

CELL_SDK ?= /usr/local/cell
CELL_MK_DIR ?= $(CELL_SDK)/samples/mk
include $(CELL_MK_DIR)/sdk.makedef.mk

PPU_SRCS 	= main.c hvcall.c core.c
PPU_TARGET 	= EBOOT.ELF

PPU_INCDIRS += -I$(CELL_TARGET_PATH)/include/
PPU_CFLAGS  += -g -Wpadded -Wall -Wformat=0
PPU_LDLIBS  += -lio_stub -lm -lfs_stub -lsysutil_stub -lsysmodule_stub

include $(CELL_MK_DIR)/sdk.target.mk
