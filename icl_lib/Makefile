# Makefile
# Created on: 2014Äê1ÔÂ23ÈÕ
#     Author: peterxmw


CC = gcc
CFLAG = -g
LDFLAGS=
OUTPUT=./debug
DIR_INC=./include
DIR_SRC=./src
DIR_OBJ=./output
DIR_BIN=

SOURCE=$(wildcard ./src/*.c)
DIR_OBJS=$(patsubst %.c, %.o, $(SOURCE))
OBJS_NAME=$(notdir $(DIR_OBJS))
OBJS=$(addprefix $(OUTPUT)/, $(OBJS_NAME))

TARGET=wyf


all:	$(TARGET)


$(TARGET):	$(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(OBJS):	$(SOURCE)
	$(CC) $(CFLAGS) -o $@ -c $(filter %$(*F).c, $(SOURCE)) -I $(DIR_INC)

clean:
	rm -f $(OBJS) $(TARGET)









#OBJ=main wyf_log wyf_array wyf_string wyf_time ./net/wyf_wrapi
#OBJS=$(OBJ:%=%.o)
#$(PROC):	$(OBJS)
#	$(CC) $(CFLAG) $(OBJS) -o $(PROC)
#	
#$(OBJS):	
#	$(CC) $(CFLAG) -c $(@:%.o=%.c) -o $(@)
#	
#clean:
#	rm -f $(OBJ:%=%.o) $(PROC)
