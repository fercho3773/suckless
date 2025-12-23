#!/bin/sh
set -e

PREFIX="${PREFIX:-/usr/local}"

PROGRAMS="
blocks
dwm
menu
slock
terminal
"

for prog in $PROGRAMS; do
    cd "$prog"

    if [ -f config.mk ]; then
        sed -i "s|^PREFIX = .*|PREFIX = $PREFIX|" config.mk
    fi

    make
    sudo make install

    cd ..
done

