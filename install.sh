#!/bin/bash

set -e

#
# The script needs `sudo`
#
if [ $UID != 0 ]; then
    echo "Please, run this script as root"
    exit 1
fi

#
# Install dependencies
#
if [ $(which apt) ]; then
    apt install xorg xserver-xorg
elif [ $(which pacman) ]; then
    pacman -S xorg-server
elif [ $(which yum) ]; then
    yum install @base-x
else
    echo -e "package manager not supported, use 'pacman', 'apt' or 'yum'"
    exit 1
fi

rm -rf tomlc99/
git clone https://github.com/cktan/tomlc99
(cd tomlc99/ && make install prefix="../")

#
# Build the project to an executable
#
make build

#
# X11 configuration
#
XWRAPPER_CONFIG="/etc/X11/Xwrapper.config"

if [ -f $XWRAPPER_CONFIG ]; then
    # When the file exists, creates a backup
    echo "'$XWRAPPER_CONFIG' content will be replaced, a backup has been created in the same folder"
    cp $XWRAPPER_CONFIG $XWRAPPER_CONFIG.backup
else
    # When it does not exist, creates the file
    touch $XWRAPPER_CONFIG
fi

echo -e "allowed_users=anybody\nneeds_root_right=yes" > $XWRAPPER_CONFIG

#
# Give rights to run a window manager from user mode
#
sudo usermod -aG tty $USER
sudo usermod -aG video $USER

# 
#
START_MIRA="/usr/bin/startmira"
XINITRC_MIRA="/usr/bin/xinitrc.mira"

cp build/out/mirawm /usr/bin/
cp build/xinitrc.mira /usr/bin/

touch $START_MIRA
echo -e "#!/bin/bash\nxinit $XINITRC_MIRA" > $START_MIRA
chmod 777 $START_MIRA

#
#
echo "Please, disable your desktop manager (lightdm, sddm, ...). Then, reboot"
