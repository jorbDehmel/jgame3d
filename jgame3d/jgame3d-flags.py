#!/bin/python3

# Rewritten in python because I know it better than bash

import sys

if __name__ == "__main__":
    if len(sys.argv) == 1:
        print(
            "-I/usr/include/SDL2 -D_REENTRANT -lSDL2 -lSDL2_ttf /usr/include/jgame3d/bin/jgame3d.a")
    elif sys.argv[1] == "--compile":
        print("-I/usr/include/SDL2 -D_REENTRANT")
    elif sys.argv[1] == "--link":
        print("-lSDL2 -lSDL2_ttf /usr/include/jgame3d/bin/jgame3d.a")
    else:
        raise Exception("Invalid command")
