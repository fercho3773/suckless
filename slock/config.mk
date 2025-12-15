# slock version
VERSION = 1.6

# Customize below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

X11INC = /usr/X11R6/include
X11LIB = /usr/X11R6/lib

# includes and libs
INCS = -I. -I/usr/include -I${X11INC}
LIBS = -L/usr/lib -lc -lcrypt -L${X11LIB} -lX11 -lXext -lXrandr ${XINERAMA} ${PAM} -lImlib2

# flags
CPPFLAGS = -DVERSION=\"${VERSION}\" -D_DEFAULT_SOURCE -DHAVE_SHADOW_H ${XINERAMAFLAGS} ${BSD} ${NETBSD}
CFLAGS = -std=c99 -pedantic -Wall ${INCS} ${CPPFLAGS} -Os -flto -march=native
LDFLAGS = -s ${LIBS}
COMPATSRC = explicit_bzero.c
