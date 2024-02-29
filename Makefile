ROOT_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

LDLIBS := -lSDL2 -lSDL2_image
BUILD_DIR := $(ROOT_DIR)o

SRCS := $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJS := $(SRCS:%.c=%.o)

all: pacman docs

pacman: $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

docs: doxygen.cfg $(SRCS) $(HEADERS)
	doxygen doxygen.cfg

include makefile.in

board_data.h: mediasrc/board_data.csv mediasrc/board_data.py
	cd mediasrc && python board_data.py

makefile.in: premake.py $(SRCS) $(HEADERS)
	python premake.py

clean:
	rm makefile.in
	rm $(OBJS)
	rm pacman
	rm -rf $(ROOT_DIR)docs/

.PHONY: clean all