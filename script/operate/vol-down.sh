#!/bin/sh

# Dependencies:
#	alsa-utils && alsa-plugins
# Command:
#	sudo pacman -S alsa-utils alsa-plugins

# Introduction:
#	This script is going to lower the VOLUME

# Author:
#	baizeyv

# E-mail:
#	baizeyv@Gmail.com

# LET'S BEGIN!!!

/usr/bin/amixer -qM set Master 2%- umute
sh $HOME/.config/dwm/scripts/functions/notify-vol.sh &
sh /home/baizeyv/.config/dwm/scripts/statusbar/dwm-status.sh
pkill -RTMIN+3 "${STATUSBAR:-dwmblocks}"
