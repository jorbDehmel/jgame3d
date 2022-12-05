#########################

DEPS = `sdl2-config --cflags --libs`
CC = clang++
ARGS = -pedantic -Wall
STEM = $(CC) $(ARGS) $(DEPS)

#########################

main:
	mkdir -p build bin
	make bin/jgame3d.a

bin/jgame3d.a:	build/points3d.o build/points.o build/objects.o build/textures.o
	ar -rc bin/jgame3d.a build/*.o

build/points3d.o:	points3d.cpp points3d.hpp
	$(STEM) -c points3d.cpp -o build/points3d.o

build/points.o:	points.cpp points.hpp
	$(STEM) -c points.cpp -o build/points.o

build/objects.o:	objects.cpp objects.hpp
	$(STEM) -c objects.cpp -o build/objects.o

build/textures.o:	textures.cpp textures.hpp
	$(STEM) -c textures.cpp -o build/textures.o

#########################

clean:
	rm -f *.o
	rm -f build/*

pclean:
	rm -f *.out *.o
	rm -f bin/*
	rm -f build/*