ROOT_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

LDLIBS := -lSDL2 -lSDL2_image
BUILD_DIR := $(ROOT_DIR)o

SRCS := $(wildcard $(ROOT_DIR)*.c)
HEADERS := $(wildcard $(ROOT_DIR)*.h) board_data.h
OBJS := $(SRCS:%.c=%.o)

all: pacman docs

pacman: $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

docs: doxygen.cfg $(SRCS) $(wildcard *.h)
	doxygen doxygen.cfg

actor.o: $(HEADERS)
actor_pacman.o: $(HEADERS)
app.o: $(HEADERS)
board.o: $(HEADERS)
event.o: $(HEADERS)
globals.o: $(HEADERS)
main.o: $(HEADERS)
texture.o: $(HEADERS)

actor.h: $(HEADERS)
actor_pacman.h: $(HEADERS)
board.h: $(HEADERS)

board_data.h: mediasrc/board_data.csv mediasrc/board_data.py
	cd mediasrc && python board_data.py

clean:
	rm $(OBJS)
	rm pacman
	rm -rf $(ROOT_DIR)docs/

.PHONY: clean all