pacman: main.o event.o
	gcc -lSDL2 main.o event.o -o pacman
main.o: main.c event.h
	gcc -c main.c
event.o: event.c event.h
	gcc -c event.c