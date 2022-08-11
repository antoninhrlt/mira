# This file is part of "mira"
# Under the MIT License
# Copyright (c) 2022 Antonin Hérault

include build/wm.mk

_init :
	mkdir -p build/out/

build : _init wm_build

test : build
	Xephyr :100 -ac -screen 1280x720 -br &
