# Copyright 2019 Barbu Matei (matei.barbu1905@stud.acs.upb.ro)

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

SRCS=$(wildcard *.c)
OBJS=$(SRCS:%.c=%.o)
TARGETS=$(OBJS:%.o=%)

build: $(OBJS) $(TARGETS)

pack:
	zip -FSr 313CA_BarbuMatei_Tema1.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS) $(OBJS)
