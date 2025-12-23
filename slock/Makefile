# slock - simple screen locker
# See LICENSE file for copyright and license details.

include config.mk

SRC = slock.c ${COMPATSRC}
OBJ = ${SRC:.c=.o}

all: slock

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk arg.h util.h

config.h:
	cp config.def.h $@

slock: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f slock ${OBJ} slock-${VERSION}.tar.gz

dist: clean
	mkdir -p slock-${VERSION}
	cp -R LICENSE Makefile README slock.1 config.mk \
		${SRC} config.def.h arg.h util.h slock-${VERSION}
	tar -cf slock-${VERSION}.tar slock-${VERSION}
	gzip slock-${VERSION}.tar
	rm -rf slock-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f slock ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/slock
	chmod u+s ${DESTDIR}${PREFIX}/bin/slock

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/slock

#.PHONY: all clean dist install uninstall
