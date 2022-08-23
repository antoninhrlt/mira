# mira
Lightweight Linux desktop environment to entirely live like in a terminal but with windows, based on X11 and written in C

## Install
Dependencies will be automatically installed with the install script. See them [here](#dependencies).

Clone the repository and open a terminal shell and type : `make install` (it simply runs the "install.sh" script)

After reboot, you will be in the tty. After logging in, you will be able to run commands in the shell.

You can type `startmira` to start the window manager

## Uninstall
Oh, tell me why you want to uninstall it by [email](mailto:antonherault@gmail.com). Is that because you don't like it ?

Enable back your desktop manager (example width "ssdm" would be `sudo systemctl enable ssdm.service --force`)

After reboot, you will see a login screen, you go back your desktop environment !

## Shortcuts
Window management by user is almost always done from the keyboard. There are the tiling and window shortcuts :
### With keyboard
- Alt + F4 : Close the current window (the focused one)
- Alt + Tab : Switch between windows (starting from the first created window)
- Alt + Left : Tile to the left (50% width and 100% height)
- Alt + Right : Tile to the right (50% width and 100% height)
- Alt + Up : Tile to full screen (100% width and 100% height)
- Alt + Down : Tile to the bottom (100% width and 50% height)
### With mouse
- Alt + Button : Set the hover window, the current window (the focused one)
- Alt + Left button : Move the window following the mouse
- Alt + Right button : Resize the window following the mouse (from corner bottom right) 

## Test
Run `make test` to build and open an X display emulator. Then, run `DISPLAY=:100 build/out/wm.mira &` to make the window manager working.

To execute windows in the window manager, then open any graphical software you want in the wm by running `DISPLAY=:100 <application> &`.

## Configuration
This is a configuration file example as "toml" format :
```toml
[display]
scale = "1x1" # zoom used for a 1920x1080 laptop

[background]
image = { path = "~/Pictures/background.png" }

[start]
script = { path = "~/Documents/mount_data_disk.sh" }
```

## Dependencies
- [tomlc99](https://github.com/cktan/tomlc99) by [@cktan](https://github.com/cktan)
