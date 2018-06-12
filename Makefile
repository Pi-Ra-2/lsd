lsd: lsd.c errors.o help.o
	gcc -Wall -g -o lsd lsd.c errors.o help.o

errors.o: errors.c errors.h
	gcc -Wall -g -c errors.h errors.c

help.h: help.c help.h
	gcc -Wall -g -c help.h help.c

.PHONY: clean
clean:
	rm -rf *.o
.PHONY: install
install:
	cp lsd /usr/bin/
	rm ./lsd
