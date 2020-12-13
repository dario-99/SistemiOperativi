all: main 

main: test.o main.c
	gcc -o main main.c test.o -lpthread
test.o: test.c test.h
	gcc -c test.c
clean: 
	rm -rf *.o
	rm -rf main