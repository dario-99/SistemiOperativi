all: sem_ex

sem_ex: sem_ex.o procedure.o
	gcc -o sem_ex sem_ex.o procedure.o
procedure.o: procedure.c procedure.h
	gcc -c procedure.c
sem_ex.o: sem_ex.c
	gcc -c sem_ex.c

clean:
	rm -rf *.o
	rm -rf sem_ex