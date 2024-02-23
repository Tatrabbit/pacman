
LDLIBS = -lSDL2 -lSDL2_image

pacman: app.o event.o main.o texture.o board.o sprite.o
	$(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

app.o: app.h defines.h
board.o: board.h board_data.h defines.h texture.h
event.o: event.h
main.o: app.h board.h event.h sprite.h
sprite.o: sprite.h app.h texture.h defines.h
texture.o: texture.h app.h defines.h

board_data.h: board_data.csv
	python board_data.py

clean:
	rm *.o
	rm pacman
.PHONY: clean all