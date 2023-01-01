#########################

DEPS = `sdl2-config --cflags --libs`
CC = clang++
ARGS = -pedantic -Wall
STEM = $(CC) $(ARGS) $(DEPS)

#########################

install: build/ bin/ bin/jgame3d.a
	sudo rm -rf /usr/include/jgame3d
	sudo mkdir /usr/include/jgame3d
	sudo cp -r ./* /usr/include/jgame3d

bin/jgame3d.a:	build/ bin/ build/basics.o build/window.o build/resources.o build/files.o
	ar rcs bin/jgame3d.a build/basics.o build/window.o build/resources.o build/files.o

build/basics.o:	build/ bin/ basics.cpp basics.hpp
	$(STEM) -c basics.cpp -o build/basics.o

build/window.o:	build/ bin/ window.cpp window.hpp
	$(STEM) -c window.cpp -o build/window.o

build/resources.o:	build/ bin/ resources.cpp resources.hpp
	$(STEM) -c resources.cpp -o build/resources.o

build/files.o:	build/ bin/ files.cpp files.hpp
	$(STEM) -c files.cpp -o build/files.o

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