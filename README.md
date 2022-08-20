# mira
Lightweight Linux desktop environment to entirely live like in a terminal but with windows, based on X11 and written in C

## Test
Run `make test` to build and open an X display emulator. Then, run `DISPLAY=:100 build/out/wm.mira` to make the window manager working.

To execute windows in the window manager, then open any graphical software you want in the wm by running `DISPLAY=:100 <application> &`

## Install
Clone the repository `git clone https://github.com/antoninhrlt/mira`.

Disable your desktop manager (example with "ssdm" would be `sudo systemctl disable ssdm.service --force`). 

After reboot, you will be in the tty. After logging in, you will be able to run commands in the shell.

Then, type `make build` to build the project.

> The following process uses `sudo` because it's required until I don't find a way to unlock /dev/tty0 for graphics. Be careful, it means you are on a `root` session while you use the window manager.

Finally, to run the window manager, just type `sudo make run`.

> This install is neither perfect nor simple, but it works. Contribute with your installer or wait for new updates.
