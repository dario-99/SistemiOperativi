all: main procedure.o

main: main.c procedure.o
	gcc -o main main.c procedure.o -lpthread

procedure.o: procedure.h procedure.c
	gcc -c procedure.c