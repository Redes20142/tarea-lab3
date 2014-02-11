# environment variables. Compiler and its flags
CC = gcc
CFLAGS = -c -Wall -x c -I ./include/ -O2 -ffunction-sections -fdata-sections -funit-at-a-time -std=c99 -D_GNU_SOURCE

all : build

build : main.o
	$(CC) lib/main.o -o bin/tarea-lab3 # TODO add tags for all necesary libs to make the main
	chmod 774 bin/tarea-lab3

main.o :
	$(CC) $(CFLAGS) src/main.c -o lib/main.o
# TODO insert makefile tasks

clean :
	rm -f bin/*

cleanall :
	rm -f bin/* lib/*

exec :
	bin/tarea-lab3

