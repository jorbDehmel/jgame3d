STEM := clang++ -pedantic -Wall -g `sdl2-config --cflags`

jtri.o:	jtri.hpp jtri.cpp
	$(STEM) -c -o jtri.o jtri.cpp

clean:
	rm -rf *.o *.a *.out