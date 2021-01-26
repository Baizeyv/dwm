#!/bin/bash
layouts="echo -e []= Tile\n><> Float\n[M] Monocle\nTTT Bstack\n=== Bstackhoriz\n|+| Tatami\n[@] Spiral\n[\\] Dwindle\n||| Tcl\n### Horizgrid"
layout=$($layouts | dmenu -p 'Select Layout' -h 30 -l 10 -g 1 -x 800 -y 320 -z 300 "$@")

if [[ "$layout" == "[]= Tile" ]];then
    xsetroot -name "fsignal:1";
elif [[ "$layout" == "><> Float" ]];then
    xsetroot -name "fsignal:2";
elif [[ "$layout" == "[M] Monocle" ]];then
    xsetroot -name "fsignal:3";
elif [[ "$layout" == "TTT Bstack" ]];then
    xsetroot -name "fsignal:4";
elif [[ "$layout" == "=== Bstackhoriz" ]];then
    xsetroot -name "fsignal:5";
elif [[ "$layout" == "|+| Tatami" ]];then
    xsetroot -name "fsignal:6";
elif [[ "$layout" == "[@] Spiral" ]];then
    xsetroot -name "fsignal:7";
elif [[ "$layout" == "[\\] Dwindle" ]];then
    xsetroot -name "fsignal:8";
elif [[ "$layout" == "||| Tcl" ]];then
    xsetroot -name "fsignal:9";
elif [[ "$layout" == "### Horizgrid" ]];then
    xsetroot -name "fsignal:10";
fi
