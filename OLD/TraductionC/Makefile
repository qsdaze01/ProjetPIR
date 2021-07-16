all: main

main: main.o ES8388.o
	gcc -Wall main.o -o main

main.o: main.c ES8388.c
	gcc -Wall -c main.c -o main.o

ES8388.o: ES8388.c
	gcc -Wall -c ES8388.c -o ES8388.o