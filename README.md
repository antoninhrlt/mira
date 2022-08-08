# mirade
Lightweight Linux desktop environment to entirely live like in a terminal but with windows, based on X11 and written in C

## Test
You can try the window manager in a X11 emulator called "Xephyr". Run : `make wm_test`. 

To open windows in the window manager, export the display to `:100` (as set in the [makefile](Makefile#L28)) : `export DISPLAY=:100` and launch any software (example : `xterm`)
