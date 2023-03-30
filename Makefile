#########################

CC = clang++
ARGS = -pedantic -Wall
STEM = $(CC) $(ARGS)

#########################

all: bin/ build/ /usr/include/jgame3d bin/main.out

#########################

bin/main.out:	build/main.o
	$(STEM) -o bin/main.out build/main.o `jgame3d-flags --link`

#########################

build/main.o:	demos/main.cpp
	$(STEM) -c demos/main.cpp -o build/main.o `jgame3d-flags --compile`

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