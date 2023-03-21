#########################

CC = clang++
ARGS = -pedantic -Wall
STEM = $(CC) $(ARGS)

#########################

all: /usr/include/jgame3d bin/demo.out bin/stress.out

#########################

bin/demo.out:	build/demo.o
	mkdir -p bin
	$(STEM) -o bin/demo.out build/demo.o `jgame3d-flags --link`

bin/stress.out: build/stress.o
	mkdir -p bin
	$(STEM) -o bin/stress.out build/stress.o `jgame3d-flags --link`

build/demo.o:	demos/rwdemo.cpp
	mkdir -p build
	$(STEM) -c demos/rwdemo.cpp -o build/demo.o `jgame3d-flags --compile`

build/stress.o:	demos/stresstest.cpp
	mkdir -p build
	$(STEM) -c demos/stresstest.cpp -o build/stress.o `jgame3d-flags --compile`

#########################

/usr/include/jgame3d:
	$(MAKE) -C jgame3d

#########################

clean:
	rm -f *.out *.o
	rm -rf bin
	rm -rf build

#########################