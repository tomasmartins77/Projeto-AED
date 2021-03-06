CC = gcc

CFLAGS = -Wall -std=c99 -O3

TARGET = roap

OBJS = main.c	Funcionalidades.c	modos.c	Utility.c	graphs.c	PQueue.c	Utility2.c	Listas.c	Funcionalidades.h	modos.h	Utility.h	graphs.h	Utility2.h	PQueue.h	Listas.h

all: $(TARGET)

$(TARGET):	$(OBJS)
	$(CC)	$(CFLAGS)	-o	$(TARGET)	$(OBJS)

zip: $(TARGET).zip

$(TARGET).zip: Makefile $(OBJS)
	zip -9 $@ $?