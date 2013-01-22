
PREFIX=bin
CFLAGS=-O3 -pipe -DNDEBUG -Wall
CC=/usr/bin/gcc 

default: all

all: \
	clean \
  bin/user_lookup

bin/user_lookup: src/user_lookup.o

bin/%: src/%.o
	$(CC) -o $@ $< $(CFLAGS)

clean: 
	rm -f src/*.o

uninstall: 
	rm -f bin/*


