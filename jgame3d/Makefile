#########################

DEPS = `sdl2-config --cflags --libs`
CC = clang++
ARGS = -pedantic -Wall
STEM = $(CC) $(ARGS) $(DEPS)

#########################

bin/demo.out:	bin/jgame3d.a build/demo.o
	$(STEM) build/basics.o build/demo.o -o bin/demo.out

build/demo.o:	rwdemo.cpp
	$(STEM) -c rwdemo.cpp -o build/demo.o

#########################

build/basics.o:	basics.cpp basics.hpp
	$(STEM) -c basics.cpp -o build/basics.o

#########################

clean:
	rm -f *.o
	rm -f build/*

pclean:
	rm -f *.out *.o
	rm -f bin/*
	rm -f build/*