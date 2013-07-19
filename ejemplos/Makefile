#!/usr/bin/make -f

SOURCES = matrices.c param.c vec-cadenas.c vectores.c
OBJ = $(SOURCES:.c=.o)
ALL = $(SOURCES:.c=)

CC = gcc
CFLAGS  = -Wall -pedantic -g -std=c99
LDFLAGS = -Wall -pedantic -g -std=c99

all: $(ALL)

clean:
	rm -f $(OBJ) $(ALL)

.PHONY: all clean
