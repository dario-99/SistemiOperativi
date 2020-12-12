all: main procedure.o utils.o

main: procedure.o main.c utils.o
	gcc -o main main.c procedure.o utils.o
procedure.o: procedure.c procedure.h utils.o
	gcc -c procedure.c 
utils.o: utils.c utils.h
	gcc -c utils.c
clean:
	rm -rf *.o
	rm -rf main
