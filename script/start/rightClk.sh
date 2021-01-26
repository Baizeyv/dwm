#!/bin/sh

cat <<EOF | xmenu | sh &
update package	st -e /home/baizeyv/willGit/dwmblocks/script/popupgrade
test
test2
EOF
