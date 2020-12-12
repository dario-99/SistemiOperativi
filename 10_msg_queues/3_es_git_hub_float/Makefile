all: main p1 p2 p3 procedure.o

main: main.c procedure.o
	gcc -o main main.c procedure.o

p1: p1.c procedure.o
	gcc -o p1 p1.c procedure.o

p2: p2.c procedure.o
	gcc -o p2 p2.c procedure.o

p3: p3.c procedure.o
	gcc -o p3 p3.c procedure.o

procedure.o: procedure.c procedure.h
	gcc -c procedure.c

clean:
	rm -rf *.o
	rm -rf main p1 p2 p3