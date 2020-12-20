all: main procedure.o semafori.o

main: main.c procedure.o semafori.o
	gcc -o main main.c procedure.o semafori.o
procedure.o: semafori.o procedure.c procedure.h
	gcc -c procedure.c
semafori.o: semafori.c semafori.h
	gcc -c semafori.c