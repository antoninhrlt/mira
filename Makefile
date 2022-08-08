# This file is part of "mirade"
# Under the MIT License
# Copyright (c) 2022 Antonin Hérault

CC = gcc
CC_FLAGS = -W -Wall -Wextra -g -pedantic -I inc/

DEPS = -l X11

WM_SRC = $(shell find wm/ -name '*.c')
WM_OBJ = $(patsubst wm/%.c,build/wm/%.o,$(WM_SRC))

WM_BIN = build/mirawm

_wm_init :
	mkdir -p build/wm/

wm_build : _wm_init $(WM_BIN)

$(WM_BIN) : $(WM_OBJ)
	$(CC) $(CC_FLAGS) $(DEPS) -o $@ $^ 

build/wm/%.o : wm/%.c
	$(CC) $(CC_FLAGS) -c -o $@ $<

wm_test : wm_build
	xinit ./install/xinitrc -- /usr/bin/Xephyr \
		:100 \
		-ac \
		-screen 1280x720 \
		-host-cursor
