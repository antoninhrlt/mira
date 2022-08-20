# This file is part of "mira"
# Under the MIT License
# Copyright (c) 2022 Antonin Hérault

include build/wm.mk

_init :
	mkdir -p build/out/

build : _init wm_build

run : build
	xinit ./build/xinitrc

test : build
	Xephyr -ac -screen 1280x720 -br -reset -terminate 2> /dev/null :100 &
