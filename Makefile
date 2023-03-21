#########################

CC = clang++
ARGS = -pedantic -Wall
STEM = $(CC) $(ARGS)

#########################

all: bin/ build/ /usr/include/jgame3d bin/demo.out bin/stress.out bin/camtest.out

#########################

bin/demo.out:	build/demo.o
	$(STEM) -o bin/demo.out build/demo.o `jgame3d-flags --link`

bin/stress.out: build/stress.o
	$(STEM) -o bin/stress.out build/stress.o `jgame3d-flags --link`

bin/camtest.out: build/camtest.o
	$(STEM) -o bin/camtest.out build/camtest.o `jgame3d-flags --link`

build/demo.o:	demos/rwdemo.cpp
	$(STEM) -c demos/rwdemo.cpp -o build/demo.o `jgame3d-flags --compile`

build/stress.o:	demos/stresstest.cpp
	$(STEM) -c demos/stresstest.cpp -o build/stress.o `jgame3d-flags --compile`

build/camtest.o:	demos/camtest.cpp
	$(STEM) -c demos/camtest.cpp -o build/camtest.o `jgame3d-flags --compile`

#########################

bin/:
	mkdir -p bin

build/:
	mkdir -p build

#########################

/usr/include/jgame3d:
	$(MAKE) -C jgame3d

#########################

clean:
	rm -f *.out *.o
	rm -rf bin
	rm -rf build

#########################