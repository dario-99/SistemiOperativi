all: visualizzatore.o main.o semafori.o procedure.o
	gcc -o main main.o procedure.o semafori.o
	gcc -o visualizzatore visualizzatore.o semafori.o procedure.o
main: main.o procedure.o semafori.o
	gcc -o main main.o procedure.o semafori.o
visualizzatore: procedure.o semafori.o visualizzatore.o
	gcc -o visualizzatore visualizzatore.o semafori.o procedure.o
visualizzatore.o: procedure.o semafori.o visualizzatore.c
	gcc -c visualizzatore.c 
main.o: main.c semafori.o procedure.o
	gcc -c main.c 
semafori.o: semafori.h semafori.c
	gcc -c semafori.c 
procedure.o: procedure.c procedure.h semafori.o
	gcc -c procedure.c 
clean:
	rm -r *.o
	rm -r main