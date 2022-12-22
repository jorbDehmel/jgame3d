#########################

DEPS = `sdl2-config --cflags --libs`
CC = clang++
ARGS = -pedantic -Wall
STEM = $(CC) $(ARGS) $(DEPS)

#########################

build/basics.o:	build/ bin/ basics.cpp basics.hpp
	$(STEM) -c basics.cpp -o build/basics.o

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