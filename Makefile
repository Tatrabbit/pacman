LDLIBS = -lSDL2 -lSDL2_image

pacman: actor_pacman.o app.o board.o event.o globals.o main.o sprite.o texture.o
	$(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

actor_pacman.o: actor_pacman.h globals.h sprite.h
app.o: app.h globals.h
board.o: board.h board_data.h globals.h texture.h
event.o: event.h
globals.o: globals.h
main.o: actor_pacman.h app.h board.h event.h
sprite.o: sprite.h app.h texture.h globals.h
texture.o: texture.h app.h globals.h

board_data.h: board_data.csv
	python board_data.py

clean:
	rm *.o
	rm pacman
.PHONY: clean all