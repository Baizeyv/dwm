#!/bin/bash

if [ "$1" == "inc" ]; then
    light -A 10
fi

if [ "$1" == "dec" ]; then
    light -U 10
fi

BRIGHTNESS=$(light | cut -d'.' -f1)
NOTI_ID=$(notify-send.py "Backlight" "$BRIGHTNESS/100" \
                         --hint string:image-path:video-display boolean:transient:true \
                         --replaces-process "brightness-popup")
