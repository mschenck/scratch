
PREFIX=bin
CFLAGS=-O3 -pipe -DNDEBUG -Wall
CC=/usr/bin/gcc 

OBJS = src/tester.o src/singlylinked.c

default: all

all: \
	clean \
  bin/tester

bin/tester: $(OBJS)

bin/%: src/%.o
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean: 
	rm -f src/*.o

uninstall: 
	rm -f bin/*


