#########################

DEPS = `jgame3d-flags`
CC = clang++
ARGS = -pedantic -Wall
STEM = $(CC) $(ARGS)
SUFFIX = $(DEPS)

#########################

all: bin/demo.out bin/stress.out

#########################

bin/demo.out:	bin/ build/ build/demo.o
	$(STEM) -o bin/demo.out build/demo.o $(SUFFIX)

bin/stress.out: bin/ build/ build/stress.o
	$(STEM) -o bin/stress.out build/stress.o $(SUFFIX)

build/demo.o:	demos/rwdemo.cpp /usr/include/jgame3d/bin/jgame3d.a
	$(STEM) -c demos/rwdemo.cpp -o build/demo.o $(SUFFIX)

build/stress.o:	demos/stresstest.cpp /usr/include/jgame3d/bin/jgame3d.a
	$(STEM) -c demos/stresstest.cpp -o build/stress.o $(SUFFIX)

#########################

/usr/include/jgame3d/bin/jgame3d.a: jgame3d/bin/jgame3d.a
	$(MAKE) -C jgame3d

#########################

bin/:
	mkdir bin/

build/:
	mkdir build/

#########################

clean:
	rm -f *.out *.o
	rm -f bin/*
	rm -f build/*

#########################