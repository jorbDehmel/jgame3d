#########################

DEPS = `sdl2-config --cflags --libs` -lSDL2_ttf
CC = clang++
ARGS = -pedantic -Wall
STEM = $(CC) $(ARGS)
SUFFIX = $(DEPS)

#########################
# Installing dependencies:
# Debian: 	sudo apt install libsdl2-dev libsdl2-ttf-dev clang
# Arch:		sudo pacman -S sdl2 sdl2_ttf clang
#########################

install: build/ bin/ bin/jgame3d.a /usr/bin/jgame3d-flags
	sudo rm -rf /usr/include/jgame3d
	sudo mkdir /usr/include/jgame3d
	sudo cp -r ./* /usr/include/jgame3d

bin/jgame3d.a:	build/ bin/ build/basics.o build/window.o build/resources.o build/files.o build/text.o
	ar rsv bin/jgame3d.a build/basics.o build/window.o build/resources.o build/files.o build/text.o

/usr/bin/jgame3d-flags: jgame3d-flags.sh
	chmod +x jgame3d-flags.sh
	sudo cp jgame3d-flags.sh /usr/bin/jgame3d-flags

build/basics.o:	build/ bin/ src/basics.cpp basics.hpp
	$(STEM) -c src/basics.cpp -o build/basics.o $(SUFFIX)

build/window.o:	build/ bin/ src/window.cpp window.hpp
	$(STEM) -c src/window.cpp -o build/window.o $(SUFFIX)

build/resources.o:	build/ bin/ src/resources.cpp resources.hpp
	$(STEM) -c src/resources.cpp -o build/resources.o $(SUFFIX)

build/files.o:	build/ bin/ src/files.cpp files.hpp
	$(STEM) -c src/files.cpp -o build/files.o $(SUFFIX)

build/text.o:	build/ bin/ src/text.cpp text.hpp
	$(STEM) -c src/text.cpp -o build/text.o $(SUFFIX)

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