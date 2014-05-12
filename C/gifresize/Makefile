
PREFIX = bin
PKG_CONFIG_PATH = /usr/local/ImageMagick/lib/pkgconfig
CFLAGS = -O3 -pipe -DNDEBUG -Wall -L/usr/local/ImageMagick/lib -I/usr/local/ImageMagick/include/ImageMagick-6 `PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --cflags --libs MagickWand`
CC = /usr/bin/gcc 

default: all

all: \
	clean \
  bin/resize_animation

bin/resize_animation: src/resize_animation.o

bin/%: src/%.o
	$(CC) -o $@ $< $(CFLAGS)

clean: 
	rm -f src/*.o

uninstall: 
	rm -f bin/*

