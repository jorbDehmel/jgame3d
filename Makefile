DEPS = `sdl2-config --cflags --libs`
CC = clang++
ARGS = -pedantic -Wall
STEM = $(CC) $(ARGS) $(DEPS)

main.out:	demo.o points.o
	$(STEM) points.o demo.o -o main.out

demo.o:	demo.cpp
	$(STEM) -c demo.cpp -o demo.o

points.o:	points.cpp points.hpp
	$(STEM) -c points.cpp -o points.o

pclean:
	rm -f *.out *.o