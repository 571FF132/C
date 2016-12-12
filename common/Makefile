CC=gcc
CFLAGS=-Wall -g

PROGS= commonprintf

all: $(PROGS)

commonprintf: commonprintf.o 
	$(CC) $(CFLAGS) $^ -o $@

clean:
	/bin/rm -f *.o $(PROGS) a.out core
