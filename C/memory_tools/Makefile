
PREFIX=bin
CFLAGS=-O3 -pipe -DNDEBUG -Wall
CC=/usr/bin/gcc 

default: all

all: \
	clean \
	bin/page_size \
  bin/type_sizes

bin/page_size: src/page_size.o
bin/type_sizes: src/type_sizes.o

bin/%: src/%.o
	$(CC) -o $@ $< $(CFLAGS)

clean: 
	rm -f src/*.o

uninstall: 
	rm -f bin/*


