STEM := clang++ -pedantic -Wall -g  `sdl2-config --libs --cflags`

main.out:	main.cpp ../jtri.o
	$(STEM) -o main.out main.cpp ../jtri.o

../jtri.o:
	$(MAKE) -C ..

clean:
	rm -rf *.o *.a *.out