
ifdef COMSPEC 				#WINDOWS
	MV ?= move
	RM ?= del
	OUTPUT_ROOT := d
	#GCC_HOME := c:/gnu/usr/bin
	EXE := .exe
else						#LINUX & UNIX
	MV ?= mv -f
	RM ?= rm -f
	OUTPUT_ROOT := $(HOME)
	GCC_HOME := /usr/bin
	EXE :=
endif

MKDIR = mkdir -p
OUTPUT_DIR := $(OUTPUT_ROOT)/work/binaries
app = MathTest
#CC := $(GCC_HOME)/gcc
BUILD ?= debug
BIN_DIR = bin
ifdef RELEASE
	#${MKDIR} d
else
	#${MKDIR} d
endif

#dependencies := $(subst .c,.d,$(sources))
#include_dirs := ../include
#CPPFLAGS += $(addprefix -I ,$(include_dirs))

#vpath %.h $(include_dirs)
