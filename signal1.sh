#!/bin/bash
layouts="echo -e test"
layout=$($layouts | dmenu "$@")

if [[ "$layout" == "test" ]];then xsetroot -name "fsignal:1"; fi
