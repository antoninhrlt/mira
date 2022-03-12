# This file is part o "mirade"
# Under the MIT license
# Copyright (c) mirade-org, Antonin Hérault

build :
	$(MAKE) -C mirawm/ build install

install : build
	sudo cp -f mirade.sh /bin/
	sudo cp -f mirade.desktop /usr/share/xsessions/
