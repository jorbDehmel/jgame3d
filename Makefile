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

bin/jgame3d.a:	/usr/include/jgame3d/bin/jgame3d.a
	cp /usr/include/jgame3d/bin/jgame3d.a bin/jgame3d.a

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