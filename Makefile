CMD = gcc
BIN = ./bin
CFLAGS = -Wextra -Wall -march=native -O3
UTIL = ./util
CDEPS = $(UTIL)/convert.c $(UTIL)/file.c $(UTIL)/socket.c
ODEPS = convert.o file.o socket.o

all: server client clean

server: server.o $(ODEPS)
	$(CMD) -o $(BIN)/server server.o $(ODEPS)

client: client.o $(ODEPS)
	$(CMD) -o $(BIN)/client client.o $(ODEPS)

server.o: server.c $(CDEPS)
	$(CMD) -c server.c $(CDEPS) $(CFLAGS)

client.o: client.c $(CDEPS)
	$(CMD) -c client.c $(CDEPS) $(CFLAGS)

.PHONY: clean

clean:
	rm -rf *.o