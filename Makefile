#########################

DEPS = `sdl2-config --cflags --libs`
CC = clang++
ARGS = -pedantic -Wall
STEM = $(CC) $(ARGS) $(DEPS)

#########################

bin/demo.out:	bin/ build/ build/demo.o bin/jgame3d.a
	$(STEM) -o bin/demo.out build/demo.o bin/jgame3d.a

bin/stress.out: bin/ build/ build/stress.o bin/jgame3d.a
	$(STEM) -o bin/stress.out build/stress.o bin/jgame3d.a

build/demo.o:	demos/rwdemo.cpp
	$(STEM) -c demos/rwdemo.cpp -o build/demo.o

build/stress.o:	demos/stresstest.cpp
	$(STEM) -c demos/stresstest.cpp -o build/stress.o

#########################

bin/jgame3d.a:	build/basics.o build/window.o build/resources.o build/files.o
	ar rsv bin/jgame3d.a build/basics.o build/window.o build/resources.o build/files.o

#########################

build/basics.o:	jgame3d/basics.cpp jgame3d/basics.hpp
	$(STEM) -c jgame3d/basics.cpp -o build/basics.o

build/window.o:	jgame3d/window.cpp jgame3d/window.hpp
	$(STEM) -c jgame3d/window.cpp -o build/window.o

build/resources.o:	jgame3d/resources.cpp jgame3d/resources.hpp
	$(STEM) -c jgame3d/resources.cpp -o build/resources.o

build/files.o:	jgame3d/files.cpp jgame3d/files.hpp
	$(STEM) -c jgame3d/files.cpp -o build/files.o

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