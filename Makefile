#########################

DEPS = `sdl2-config --cflags --libs`
CC = clang++
ARGS = -pedantic -Wall
STEM = $(CC) $(ARGS) $(DEPS)

#########################

bin/demo.out:	bin/ build/ build/basics.o build/window.o build/demo.o
	$(STEM) build/basics.o build/window.o build/demo.o -o bin/demo.out

bin/stress.out: build/basics.o build/window.o build/stress.o
	$(STEM) build/basics.o build/window.o build/stress.o -o bin/stress.out

build/demo.o:	demos/rwdemo.cpp
	$(STEM) -c demos/rwdemo.cpp -o build/demo.o

build/stress.o:	demos/stresstest.cpp
	$(STEM) -c demos/stresstest.cpp -o build/stress.o

build/basics.o:	jgame3d/basics.cpp jgame3d/basics.hpp
	$(STEM) -c jgame3d/basics.cpp -o build/basics.o

build/window.o:	jgame3d/window.cpp jgame3d/window.hpp
	$(STEM) -c jgame3d/window.cpp -o build/window.o

#########################

bin/:
	mkdir bin/

build/:
	mkdir build/

#########################

clean:
	rm -f *.o
	rm -f build/*

pclean:
	rm -f *.out *.o
	rm -f bin/*
	rm -f build/*

#########################