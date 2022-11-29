#########################

DEPS = `sdl2-config --cflags --libs`
CC = clang++
ARGS = -pedantic -Wall
STEM = $(CC) $(ARGS) $(DEPS)

#########################

demo.out:	demo.o points.o points3d.o
	$(STEM) demo.o points.o points3d.o -o demo.out

ship.out:	ship.o points.o
	$(STEM) points.o ship.o -o ship.out

#########################

ship.o:	demos/ship.cpp
	$(STEM) -c demos/ship.cpp -o ship.o

demo.o:	demos/demo3d.cpp
	$(STEM) -c demos/demo3d.cpp -o demo.o

#########################

points3d.o:	points3d.cpp points3d.hpp
	$(STEM) -c points3d.cpp -o points3d.o

points.o:	points.cpp points.hpp
	$(STEM) -c points.cpp -o points.o

#########################

pclean:
	rm -f *.out *.o