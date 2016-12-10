CC=gcc
CFLAGS=-Wall -g

PROGS= common

all: $(PROGS)

common: common.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	/bin/rm -f *.o $(PROGS) a.out core
