pacman: main.o event.o
	gcc -lSDL2 -g main.o event.o -o pacman
main.o: main.c event.h
	gcc -c -g main.c
event.o: event.c event.h
	gcc -c -g event.c