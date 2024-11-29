CC = gcc
CFLAGS = -Wall -g -std=c99
OBJ = main.o mmu.o util.o list.o

mmu: $(OBJ)
	$(CC) $(CFLAGS) -o mmu $(OBJ)

main.o: main.c util.h list.h mmu.h
	$(CC) $(CFLAGS) -c main.c

mmu.o: mmu.c util.h list.h mmu.h
	$(CC) $(CFLAGS) -c mmu.c

util.o: util.c util.h list.h
	$(CC) $(CFLAGS) -c util.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

clean:
	rm -f *.o mmu