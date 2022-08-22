# This file is part of "mira"
# Under the MIT License
# Copyright (c) 2022 Antonin Hérault

# Build file for the wm

include build/config.mk

CC_FLAGS = $(CC_DEBUG_FLAGS) -I inc/wm -I inc/

OUT_DIR = build/out/wm

SRC = $(shell find src/wm -name '*.c')
OBJ = $(patsubst src/wm/%.c, $(OUT_DIR)/%.o,$(SRC)) $(OUT_DIR)/x11.o

BIN = build/out/wm.mira

_wm_init : 
	mkdir -p $(OUT_DIR)

wm_build : _wm_init $(BIN)

$(BIN) : $(OBJ)
	$(CC) $(CC_DEPS) $(CC_FLAGS) -o $@ $^

$(OUT_DIR)/%.o : src/wm/%.c
	$(CC) $(CC_DEPS) $(CC_FLAGS) -c -o $@ $^

$(OUT_DIR)/x11.o : src/x11.c
	$(CC) $(CC_DEPS) $(CC_FLAGS) -c -o $@ $^
