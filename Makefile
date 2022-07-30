# This file is part of "mirade"
# Under the MIT License
# Copyright (c) 2022 Antonin Hérault

CC = gcc
CC_FLAGS = -W -Wall -Wextra -g -pedantic -I inc/

SRC = $(shell find src/ -name '*.c')
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))

BIN = build/mirade

_init :
	mkdir -p build/wm/

build : _init $(BIN)

$(BIN) : $(OBJ)
	$(CC) $(CC_FLAGS) -o $@ $^ 

build/%.o : src/%.c
	$(CC) $(CC_FLAGS) -c -o $@ $<
