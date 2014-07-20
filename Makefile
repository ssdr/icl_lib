# Makefile
# Created on: 2014Äê1ÔÂ23ÈÕ
#     Author: peterxmw


CC = gcc
CFLAG = -g
LDFLAGS=
OUTPUT=./debug
DIR_INC=./
DIR_SRC=./src
DIR_OBJ=./output

SOURCE=$(wildcard ./src/*.c)
DIR_OBJS=$(patsubst %.c, %.o, $(SOURCE))
OBJS_NAME=$(notdir $(DIR_OBJS))
OBJS=$(addprefix $(OUTPUT)/, $(OBJS_NAME))

TARGET=icl_lib


all:	$(TARGET)


$(TARGET):	$(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(OBJS):	$(SOURCE)
	$(CC) $(CFLAGS) -o $@ -c $(filter %$(*F).c, $(SOURCE)) -I $(DIR_INC)

clean:
	rm -f $(OBJS) $(TARGET)


