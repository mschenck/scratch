
PREFIX=bin
CC=/usr/bin/gcc 

OS := $(shell uname)
ifeq ($(OS), Darwin)
  # MacOS 
  CFLAGS = -fno-strict-aliasing -O3 -march=core2 -msse4.1 -w -pipe -DNDEBUG -g -fwrapv -Wall -Wstrict-prototypes -lcurses
else
  # Linux
  CFLAGS = -fno-strict-aliasing -O3 -w -pipe -DNDEBUG -g -fwrapv -Wall -Wstrict-prototypes
endif

OBJS = src/hash_compare.o src/hashers.o

default: all

all: \
	clean \
	bin/hash_compare

bin/hash_compare: $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

bin/%: src/%.o
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

src/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean: 
	rm -f src/*.o

uninstall: 
	rm -f bin/*


