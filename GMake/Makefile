#make file
INC_DIR := includes
SOURCE_DIR := Src
BIN_DIR =: bin 
CC = gcc
CPPFLAGS = -I $(INC_DIR)
SOURCES = main.c MathHelper.c
LIBS = MathHelper.a
LPATHS = -L .
AR = ar
ARFLAGS = rv

#vpath %.c $(SOURCE_DIR)
#vpath %.h $(INC_DIR)
#include $(subst .c,.d,$(SOURCES))

include common.mk

all clean:
	cd 'Src' && $(MAKE) $@
	cd 'bin' && $(MAKE) $@



#all: MathHelper.o
#	$(CC) -o $@ $<
	
#MathHelper.o:
#	$(CC) $(CPPFLAGS) -c $< -o MathHelper.o

.PHONY: all clean

