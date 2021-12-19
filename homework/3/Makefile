# Copyright 2019 Barbu Matei (matei.barbu1905@stud.acs.upb.ro)

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -I.

SRCS=$(wildcard *.c)
OBJS=$(SRCS:%.c=%.o)
TARGET=archiver

build: 
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

pack:
	zip -FSr 313CA_BarbuMatei_Tema3.zip README Makefile *.c *.h

clean:
	rm -f $(TARGET) $(OBJS)
