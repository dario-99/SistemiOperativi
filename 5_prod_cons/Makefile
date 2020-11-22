app = prod_cons
dep = prod_cons.o semafori.o procedure.o

all: ${dep}
	gcc -o ${app} ${dep}

${app}: ${dep}
	gcc -o ${app} ${dep}

prod_cons.o: semafori.o procedure.o
	gcc -c prod_cons.c 

semafori.o: semafori.c semafori.h
	gcc -c semafori.c

procedure.o: procedure.c procedure.h
	gcc -c procedure.c	

clean:
	rm -rf *.o
	rm -rf ${app}