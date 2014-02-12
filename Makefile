# environment variables. Compiler and its flags
CC = gcc
CFLAGS = -c -Wall -x c -I ./include/ -O2 -ffunction-sections -fdata-sections -funit-at-a-time -std=c99 -D_GNU_SOURCE

all : build

build : main.o masker.o
	$(CC) lib/main.o -o bin/tarea-lab3
	chmod 774 bin/tarea-lab3

main.o :
	$(CC) $(CFLAGS) src/main.c -o lib/main.o

clean :
	rm -f bin/*

cleanall :
	rm -f bin/* lib/*

exec :
	bin/tarea-lab3

masker.o :
	$(CC) $(CFLAGS) src/masker.c -o lib/masker.o

