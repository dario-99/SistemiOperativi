all: main.o procedure.o
	gcc -o main main.o procedure.o

main: main.o procedure.o
	gcc -o main main.o procedure.o

main.o: main.c procedure.o
	gcc -c main.c

procedure.o: procedure.h procedure.c
	gcc -c procedure.c

clean:
	rm -rf *.o
	rm -rf main