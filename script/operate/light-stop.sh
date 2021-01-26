#!/bin/sh

# light -S 10
xbacklight -set 1
sh $HOME/.config/dwm/scripts/functions/notify-light.sh &
