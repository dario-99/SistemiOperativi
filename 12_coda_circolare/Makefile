all: main.o semafori.o procedure.o
	gcc -o main main.o procedure.o semafori.o

main: main.o procedure.o semafori.o
	gcc -o main main.o procedure.o semafori.o

main.o: procedure.o semafori.o
	gcc -c main.c

procedure.o: semafori.o procedure.c procedure.h
	gcc -c procedure.c

semafori.o:	semafori.h semafori.c
	gcc -c semafori.c

clean:
	rm -rf *.o
	rm -rf main