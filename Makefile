
CC= gcc

CFLAGS= -Wall -std=c99 -O3 -g

LDFLAGS= -lm

SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRCS))
HEADERS=$(wildcard *.h)
PDFS=$(wildcard *.pdf)

TARGET= roap

all: $(TARGET)

$(TARGET): $(OBJS) Makefile
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

%.o: %.c $(HEADERS) Makefile
	$(CC) -c $(CFLAGS) -o $@ $<

zip: $(TARGET).zip

$(TARGET).zip: Makefile $(SRCS) $(HEADERS) $(PDFS)
	zip -9 $@ $?

tgz: $(TARGET).tar.gz

$(TARGET).tar.gz: Makefile $(SRCS) $(HEADERS) $(PDFS)
	tar czvf $@ $^

clean:
	rm -f *.o $(TARGET)
