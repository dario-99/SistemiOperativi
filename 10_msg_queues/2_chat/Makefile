all: server.o client.o msglib.o
	gcc -o server server.o msglib.o
	gcc -o client client.o msglib.o

server: server.o msglib.o
	gcc -o server server.o msglib.o

client: client.o msglib.o
	gcc -o client client.o msglib.o

client.o: client.c msglib.o
	gcc -c client.c
	
server.o: server.c msglib.o
	gcc -c server.c

msglib.o: msglib.c msglib.h
	gcc -c msglib.c

clean:
	rm -rf *.o
	rm -rf client
	rm -rf server