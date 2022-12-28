#########################

DEPS = `sdl2-config --cflags --libs`
CC = clang++
ARGS = -pedantic -Wall
STEM = $(CC) $(ARGS) $(DEPS)

#########################

install: build/basics.o build/window.o
	sudo mkdir -p /usr/include/jgame3d
	sudo cp -r ./* /usr/include/jgame3d

build/basics.o:	build/ bin/ basics.cpp basics.hpp
	$(STEM) -c basics.cpp -o build/basics.o

build/window.o:	build/ bin/ window.cpp window.hpp
	$(STEM) -c window.cpp -o build/window.o

build/:
	mkdir build

bin/:
	mkdir bin

#########################

clean:
	rm -f *.o
	rm -f build/*

pclean:
	rm -f *.out *.o
	rm -f bin/*
	rm -f build/*

#########################