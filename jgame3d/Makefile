#########################

CC = clang++
ARGS = -pedantic -Wall
STEM = $(CC) $(ARGS)
C_SUFFIX = `sdl2-config --cflags`

#########################
# Installing dependencies:
# Debian: 	sudo apt install libsdl2-dev libsdl2-ttf-dev clang
# Arch:		sudo pacman -S sdl2 sdl2_ttf clang
#########################

install: build/ bin/ bin/jgame3d.a /usr/bin/jgame3d-flags
	sudo rm -rf /usr/include/jgame3d
	sudo mkdir /usr/include/jgame3d

	sudo cp *.hpp /usr/include/jgame3d
	sudo cp bin/jgame3d.a /usr/include/jgame3d/jgame3d.a

uninstall:
	sudo rm -rf /usr/include/jgame3d
	sudo rm -rf /usr/bin/jgame3d-flags

bin/jgame3d.a:	build/basics.o build/window.o build/resources.o build/files.o build/text.o build/scaling.o
	ar rsv bin/jgame3d.a build/basics.o build/window.o build/resources.o build/files.o build/text.o build/scaling.o

/usr/bin/jgame3d-flags: jgame3d-flags.py
	chmod +x jgame3d-flags.py
	sudo cp jgame3d-flags.py /usr/bin/jgame3d-flags

#########################

build/basics.o:	src/basics.cpp basics.hpp
	$(STEM) -c src/basics.cpp -o build/basics.o $(C_SUFFIX)

build/window.o:	src/window.cpp window.hpp
	$(STEM) -c src/window.cpp -o build/window.o $(C_SUFFIX)

build/resources.o:	src/resources.cpp resources.hpp
	$(STEM) -c src/resources.cpp -o build/resources.o $(C_SUFFIX)

build/files.o:	src/files.cpp files.hpp
	$(STEM) -c src/files.cpp -o build/files.o $(C_SUFFIX)

build/text.o:	src/text.cpp text.hpp
	$(STEM) -c src/text.cpp -o build/text.o $(C_SUFFIX)

build/scaling.o:	src/scaling.cpp scaling.hpp
	$(STEM) -c src/scaling.cpp -o build/scaling.o $(C_SUFFIX)

#########################

build/:
	mkdir build

bin/:
	mkdir bin

#########################

clean:
	rm -f *.out *.o
	rm -f bin/*
	rm -f build/*

#########################