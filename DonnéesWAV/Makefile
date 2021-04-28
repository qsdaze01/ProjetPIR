all: main

main: main.o
	gcc -Wall -g main.o -o main -lm

main.o: main.c
	gcc -c -Wall -g main.c -o main.o -lm

clean:
	rm -f main *.o