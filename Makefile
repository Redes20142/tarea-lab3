# environment variables. Compiler and its flags
CC = gcc
CFLAGS = -c -Wall -x c -I ./include/ -O2 -ffunction-sections -fdata-sections -funit-at-a-time -std=c99 -D_GNU_SOURCE

all : build

build : main.o masker_main server.o build_ex5
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

clean_ex1 :
	rm bin/masker

clean_ex4 :
	rm bin/client
	rm bin/server

clean_ex5 :
	rm bin/client
	rm bin/logger-server

build_ex1 : create_masker masker_main random_lib.o
	$(CC) -lm lib/masker.o lib/random_lib.o lib/masker_main.o -o bin/masker

build_ex4 : server.o client.o
	$(CC) lib/server.o -o bin/server
	$(CC) lib/client.o -o bin/client

build_ex5 : logger-server.o client.o build_ex1 random_lib.o create_masker
	$(CC) -lm lib/logger-server.o lib/masker.o lib/random_lib.o -o bin/logger-server
	$(CC) lib/client.o -o bin/client
	
create_masker :
	$(CC) $(CFLAGS) src/masker.c -o lib/masker.o

masker_main :
	$(CC) $(CFLAGS) src/masker_main.c -o lib/masker_main.o

random_lib.o :
	$(CC) $(CFLAGS) src/random_lib.c -o lib/random_lib.o

logger-server.o :
	$(CC) $(CFLAGS) src/logger-server.c -o lib/logger-server.o

exec_ex1 :
	bin/masker

exec_ex4 :
	bin/client-server

exec_ex5 :
	bin/loggin-client-server

server.o :
	$(CC) $(CFLAGS) src/server.c -o lib/server.o

client.o :
	$(CC) $(CFLAGS) src/client.c -o lib/client.o

