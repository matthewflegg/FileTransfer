CMD = gcc
BIN = ./bin
LIBS = -lcrypt
CFLAGS = -Wextra -Wall -march=native -O3
UTIL = ./util

CDEPS = $(UTIL)/convert.c $(UTIL)/file.c $(UTIL)/socket.c $(UTIL)/auth.c
ODEPS = convert.o file.o socket.o auth.o

all: server client clean

server: server.o $(ODEPS)
	$(CMD) $(LIBS) -o $(BIN)/server server.o $(ODEPS)

client: client.o $(ODEPS)
	$(CMD) $(LIBS) -o $(BIN)/client client.o $(ODEPS)

server.o: server.c $(CDEPS)
	$(CMD) -c server.c $(CDEPS) $(CFLAGS)

client.o: client.c $(CDEPS)
	$(CMD) -c client.c $(CDEPS) $(CFLAGS)

.PHONY: clean clean_bin

clean:
	rm -rf *.o

clean_bin:
	rm -rf $(BIN)/*
	rm -rf *.o