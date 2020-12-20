all: start server client procedure.o

start:procedure.o start.c
	gcc -o start procedure.o start.c

server:procedure.o server.c
	gcc -o server server.c procedure.o -pthread

client:procedure.o client.c
	gcc -o client client.c procedure.o

procedure.o: procedure.h procedure.c
	gcc -c procedure.c 
clean:
	rm -rf *.o
	rm -rf start server client