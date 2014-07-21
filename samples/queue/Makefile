# Makefile
# Created on: 2014年1月23日
#     Author: peterxmw

CC = gcc
#CPP      = g++
CFLAG = -g
#AR      = ar
#ARFL    = rv
#RANLIB  = ranlib


OUTPUT=../debug

COMMON_INC=../../include/common
NET_INC=../../include/net
PROC_INC=./

DIR_INC=-I$(COMMON_INC) -I$(NET_INC) -I$(PROC_INC)
#暂时不需要第三方库
LDFLAGS=

COMMON_SRC=$(wildcard ../../common/*.c)
NET_SRC=$(wildcard ../../net/*.c)
PROC_SRC=$(wildcard *.c)

#ALL_SRC=$(COMMON_SRC) $(NET_SRC)

COMMON_OBJS=$(patsubst %.c, %.o, $(COMMON_SRC))
NET_OBJS=$(patsubst %.c, %.o, $(NET_SRC))
PROC_OBJS=$(patsubst %.c, %.o, $(PROC_SRC))

#a:
#	@echo "$(COMMON_SRC)"
#	@echo "$(NET_SRC)"
#	@echo "$(PROC_SRC)"


OUTPUT_COMMON_OBJS=$(addprefix $(OUTPUT)/common/, $(notdir $(COMMON_OBJS)))
OUTPUT_NET_OBJS=$(addprefix $(OUTPUT)/net/, $(notdir $(NET_OBJS)))
OUTPUT_PROC_OBJS=$(PROC_OBJS)

OBJ_DST=$(OUTPUT_COMMON_OBJS) $(OUTPUT_NET_OBJS) $(OUTPUT_PROC_OBJS)

PROC=

$(PROC):	$(OBJ_DST)
	$(CC) $(CFLAG) -o $(PROC) $(OBJ_DST)
	
#$(STATIC_LIB):	depends $(OBJ_DST)
#	$(AR) $(ARFL) -o $(OUTPUT)/$(STATIC_LIB) $(OBJ_DST)
#	$(RANLIB) $(OUTPUT)/$(STATIC_LIB)

$(OUTPUT_COMMON_OBJS):	$(COMMON_SRC)
	$(CC) $< -o $@ 	$(DIR_INC)

$(OUTPUT_NET_OBJS):	$(NET_SRC)
	$(CC) $< -o $@	$(DIR_INC)

$(OUTPUT_PROC_OBJS):	$(PROC_SRC)
	$(CC) $< -o $@	$(DIR_INC)

clean:
	rm -f $(OBJ_DST) 
	#$(PROC)

