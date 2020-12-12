all: main.o semafori.o procedure.o lettore.o scrittore.o
	gcc -o main main.o procedure.o semafori.o
	gcc -o lettore lettore.o procedure.o semafori.o
	gcc -o scrittore scrittore.o procedure.o semafori.o

main: lettore scrittore procedure.o semafori.o main.o
	gcc -o main main.o procedure.o semafori.o

lettore: lettore.o procedure.o semafori.o
	gcc -o lettore lettore.o procedure.o semafori.o

scrittore: scrittore.o procedure.o semafori.o
	gcc -o scrittore scrittore.o procedure.o semafori.o

main.o: lettore.o scrittore.o procedure.o semafori.o main.c
	gcc -c main.c

lettore.o: procedure.o semafori.o lettore.c
	gcc -c lettore.c

scrittore.o: procedure.o semafori.o scrittore.c
	gcc -c scrittore.c

procedure.o: semafori.o procedure.c procedure.h
	gcc -c procedure.c

semafori.o: semafori.c semafori.h
	gcc -c semafori.c

clean:
	rm -rf *.o
	rm -rf main
	rm -rf scrittore
	rm -rf lettore