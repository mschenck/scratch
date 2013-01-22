
PREFIX=bin
CFLAGS=-O3 -pipe -DNDEBUG -Wall
LDFLAGS=-L/lib64 -lrt
CC=/usr/bin/gcc 

default: all

all: \
	clean \
  uninstall \
  bin/ringbuffer

bin/ringbuffer: src/ringbuffer.o

bin/%: src/%.o
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

src/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean: 
	rm -f src/*.o

uninstall: 
	rm -f bin/*


