CC= gcc

CFLAGS= -Wall -std=c11 -g

SOURCE=$(wildcard *.c)
OBJECTS=$(patsubst %.c, %.o, $(SOURCE))
HEADERS=$(wildcard *.h)

END= roap

all: $(END)

$(END): $(OBJECTS) Makefile
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

%.o: %.c $(HEADERS) Makefile
	$(CC) -c $(CFLAGS) -o $@ $<