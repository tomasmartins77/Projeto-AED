CC= gcc

CFLAGS= -Wall -std=c99 -O3

TARGET= roap

roap: Utility.o Funcionalidades.o modos.o main.o
	$(CC) $(CFLAGS) -o $(TARGET) Utility.o Funcionalidades.o modos.o main.o

main.o: main.c Utility.h Funcionalidades.h modos.h
	$(CC) $(CFLAGS) -c main.c

modos.o: modos.c modos.h Funcionalidades.h Utility.h
	$(CC) $(CFLAGS) -c modos.c

Funcionalidades.o: Funcionalidades.c Funcionalidades.h Utility.h
	$(CC) $(CFLAGS) -c Funcionalidades.c

Utility.o: Utility.c Utility.h
	$(CC) $(CFLAGS) -c Utility.c

clean:
	rm -f *.o *.out $(TARGET)