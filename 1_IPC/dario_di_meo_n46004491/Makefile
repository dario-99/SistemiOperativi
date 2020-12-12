all: analizzatore elaboratore generatore main procedure.o semafori.o

main: procedure.o semafori.o analizzatore elaboratore generatore
	gcc -o main main.c procedure.o semafori.o

generatore: generatore.c procedure.o semafori.o
	gcc -o generatore generatore.c procedure.o semafori.o

analizzatore: analizzatore.c procedure.o semafori.o
	gcc -o analizzatore analizzatore.c procedure.o semafori.o

elaboratore: elaboratore.c procedure.o semafori.o
	gcc -o elaboratore elaboratore.c procedure.o semafori.o

procedure.o: procedure.c procedure.h semafori.o
	gcc -c procedure.c

semafori.o: semafori.c semafori.h
	gcc -c semafori.c

clean:
	rm -rf *.o
	rm -rf analizzatore elaboratore generatore main