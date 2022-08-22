# mira
Lightweight Linux desktop environment to entirely live like in a terminal but with windows, based on X11 and written in C

## Install
Install "xorg-server" package (check the correct name according to your package manager).

Edit (as sudo) "/etc/X11/Xwrapper.config" by writing in it :
```config
allowed_users=anybody
needs_root_right=yes
```
Save the document.

Now, give you the rights to run a window manager from user mode :
```
sudo usermod -aG tty <username>
sudo usermod -aG video <username>
```

Disable your desktop manager (example with "ssdm" would be `sudo systemctl disable ssdm.service --force`). 

After reboot, you will be in the tty. After logging in, you will be able to run commands in the shell.

Clone the repository. Then, type `make build` in the repository folder to build the project.

Finally, to run the window manager, just type `make run`.

> This install is neither perfect nor simple, but it works. Contribute with your installer or wait for new updates.

## Uninstall
Oh, tell me why you want to uninstall it by [email](mailto:antonherault@gmail.com). Is that because you don't like it ?

Enable back your desktop manager (example width "ssdm" would be `sudo systemctl enable ssdm.service --force`)

After reboot, you will see a login screen, you go back your desktop environment !

## Contribute
- ## Pull request
    Fork this repository, make changes then open a pull request. It will be checked as soon as possible.
- ## Test
    Run `make test` to build and open an X display emulator. Then, run `DISPLAY=:100 build/out/wm.mira &` to make the window manager working.

    To execute windows in the window manager, then open any graphical software you want in the wm by running `DISPLAY=:100 <application> &`.
- ## Assets
    Same as pull request, don't hesitate to create assets about *mira* and put them in the project.
