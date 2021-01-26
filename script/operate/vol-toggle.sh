#!/bin/sh

# Dependencies:
#	alsa-utils && alsa-plugins
# Command:
#	sudo pacman -S alsa-utils alsa-plugins

# Introduction:
#	This script is going to open/close the VOLUME

# Author:
#	baizeyv

# E-mail:
#	baizeyv@Gmail.com

# LET'S BEGIN!!!

/usr/bin/amixer set Master toggle
sh $HOME/.config/dwm/scripts/functions/notify-vol.sh &
sh /home/baizeyv/.config/dwm/scripts/statusbar/dwm-status.sh
pkill -RTMIN+3 "${STATUSBAR:-dwmblocks}"
