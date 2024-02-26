LDLIBS = -lSDL2 -lSDL2_image

pacman: actor.o actor_pacman.o app.o board.o event.o globals.o main.o texture.o
	$(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

actor.o: actor.h texture.h
actor_pacman.o: actor_pacman.h actor.o board.h globals.h
app.o: app.h globals.h
board.o: board.h board_data.h globals.h texture.h
event.o: event.h
globals.o: globals.h
main.o: actor_pacman.h app.h board.h event.h
texture.o: texture.h app.h globals.h

actor.h: globals.h
actor_pacman.h: actor.h
board.h: globals.h

board_data.h: mediasrc/board_data.csv mediasrc/board_data.py
	cd mediasrc && python board_data.py

clean:
	rm *.o
	rm pacman
.PHONY: clean all