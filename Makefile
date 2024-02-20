
LDLIBS = -lSDL2 -lSDL2_image

pacman: app.o event.o main.o texture.o
	$(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

app.o: app.h
event.o: event.h
main.o: event.h app.h sprite.h texture.h
texture.o: texture.h app.h

clean:
	rm *.o
	rm pacman
.PHONY: clean all