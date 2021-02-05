# music

# screen
xrandr --output HDMI-1-1 --mode 1920x1080 --auto --primary --output eDP-1-1 --auto --right-of HDMI-1-1

# status bar
dwmblocks &

# fcitx
fcitx5 &

# notify client
# deadd-notification-center &
dunst &

# network manage
nm-applet &

# picom
picom --experimental-backends -b

# wallpaper
feh --bg-fill /home/baizeyv/Aurora/Git/pictures/0107.jpg

# udiskie
udiskie -a -n -s &

# screen lock
# xset s 300 5
# xss-lock -n /usr/lib/xsecurelock/dimmer -l --xsecurelock &

# keyboard
# vim
setxkbmap us colemak -option -option caps:swapescape -option ctrl:swap_lwin_lctl -option ctrl:swap_rwin_rctl -option lv3:ralt_alt
# emacs
# setxkbmap us colemak -option -option caps:swapescape -option altwin:swap_lalt_lwin -option ctrl:swap_rwin_rctl -option lv3:ralt_alt
xset r rate 250 30

# proxy
clash -d /home/baizeyv/.config/clash/ &

sleep 10
sh /home/baizeyv/willGit/dwmblocks/script/while_pkg.sh &
