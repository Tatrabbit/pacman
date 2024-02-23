
LDLIBS = -lSDL2 -lSDL2_image

pacman: app.o event.o main.o texture.o board.o
	$(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

app.o: app.h
board.o: board.h board_data.h defines.h
event.o: event.h
main.o: event.h app.h sprite.h texture.h
texture.o: texture.h app.h

board_data.h: board_data.csv
	python board_data.py

clean:
	rm *.o
	rm pacman
.PHONY: clean all