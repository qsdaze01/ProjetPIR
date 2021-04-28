all: DonneesWAV

main: DonneesWAV.o
	gcc -Wall -g DonneesWAV.o -o DonneesWAV -lm

main.o: main.c
	gcc -c -Wall -g DonneesWAV.c -o DonneesWAV.o -lm

clean:
	rm -f DonneesWAV *.o