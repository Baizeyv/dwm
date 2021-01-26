#!/bin/sh
killall picom
if [ $? != 0 ]; then
    picom --experimental-backends -b
fi
