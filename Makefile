LDLIBS = -lSDL2 -lSDL2_image

pacman: actor_pacman.o app.o event.o main.o texture.o board.o sprite.o
	$(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

actor_pacman.o: actor_pacman.h sprite.h
app.o: app.h defines.h
board.o: board.h board_data.h defines.h texture.h
event.o: event.h
main.o: actor_pacman.h app.h board.h event.h
sprite.o: sprite.h app.h texture.h defines.h
texture.o: texture.h app.h defines.h

board_data.h: board_data.csv
	python board_data.py

clean:
	rm *.o
	rm pacman
.PHONY: clean all