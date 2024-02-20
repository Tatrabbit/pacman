LDLIBS := -lSDL2 -lSDL2_image
all: pacman

pacman: main.o event.o app.o pacman.o
main.o: main.c event.h app.h
event.o: event.c event.h
app.o: app.h
pacman.o: pacman.c pacman.h app.h

clean:
	rm *.o
	rm pacman

.PHONY: clean all