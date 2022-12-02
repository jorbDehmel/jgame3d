#########################

DEPS = `sdl2-config --cflags --libs`
CC = clang++
ARGS = -pedantic -Wall
STEM = $(CC) $(ARGS) $(DEPS)

#########################

bin/demo.out:	build/demo.o build/points.o build/points3d.o build/objects.o
	$(STEM) build/demo.o build/points.o build/points3d.o build/objects.o -o bin/demo.out

bin/ship.out:	build/ship.o build/points.o
	$(STEM) build/points.o build/ship.o -o bin/ship.out

#########################

build/ship.o:	demos/ship.cpp
	$(STEM) -c demos/ship.cpp -o build/ship.o

build/demo.o:	demos/demo3d.cpp
	$(STEM) -c demos/demo3d.cpp -o build/demo.o

#########################

build/points3d.o:	jgame3D/points3d.cpp jgame3D/points3d.hpp
	$(STEM) -c jgame3D/points3d.cpp -o build/points3d.o

build/points.o:	jgame3D/points.cpp jgame3D/points.hpp
	$(STEM) -c jgame3D/points.cpp -o build/points.o

build/objects.o:	jgame3D/objects.cpp jgame3D/objects.hpp
	$(STEM) -c jgame3D/objects.cpp -o build/objects.o

build/collisions.o:	jgame3D/collisions.cpp jgame3D/collisions.hpp
	$(STEM) -c jgame3D/collisions.cpp -o build/collisions.o

#########################

clean:
	rm -f *.o
	rm -f build/*

pclean:
	rm -f *.out *.o
	rm -f bin/*
	rm -f build/*