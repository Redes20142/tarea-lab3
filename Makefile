# environment variables. Compiler and its flags
CC = gcc
CFLAGS = -c -Wall -x c -I ./include/ -O2 -ffunction-sections -fdata-sections -funit-at-a-time -std=c99 -D_GNU_SOURCE

all : build

build : main.o build_ex1 build_ex4
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

build_ex1 : create_masker random_lib.o
	$(CC) -lm lib/masker.o lib/random_lib.o -o bin/masker

build_ex4 : client-server.o
	$(CC) lib/client-server.o -o bin/client-server
	
create_masker :
	$(CC) $(CFLAGS) src/masker.c -o lib/masker.o

random_lib.o :
	$(CC) $(CFLAGS) src/random_lib.c -o lib/random_lib.o

exec_ex1 :
	bin/masker

exec_ex4 :
	bin/client-server

client-server.o :
	$(CC) $(CFLAGS) src/client-server.c -o lib/client-server.o

