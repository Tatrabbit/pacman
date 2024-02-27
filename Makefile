ROOT_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

LDLIBS := -lSDL2 -lSDL2_image
BUILD_DIR := $(ROOT_DIR)o

SRCS := $(wildcard $(ROOT_DIR)*.c)
OBJS := $(SRCS:%.c=%.o)

all: pacman docs

pacman: $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

docs: doxygen.cfg $(SRCS) $(wildcard *.h)
	doxygen doxygen.cfg

actor.o: actor.h texture.h
actor_pacman.o: actor_pacman.h actor.h board.h globals.h
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
	rm $(OBJS)
	rm pacman
	rm -rf $(ROOT_DIR)docs/

.PHONY: clean all