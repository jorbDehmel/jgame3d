~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

jgame3d - 3D rendering library for C++

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Jordan "Jorb" Dehmel, 2022 - present
jdehmel@outlook.com
github.com/jorbDehmel/jgame3d
This library is protected by the GPLv3
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Installation:

    This library only supports Linux. It requires SDL2,
which will need to be installed with this library. The
following commands should work for their respective
distros:

Debian:
    sudo apt-get install libsdl2-dev libsdl2-ttf-dev clang

Arch:
    sudo pacman -S sdl2 sdl2_ttf clang

    With enough fiddling around, you could probably get
this to work with macOS, and if you're really dedicated,
maybe Windows, but it's guarenteed to work with Linux
(WSL is a great resource).

    To install this library, open this folder in
terminal and enter `make install`. From then on, you can
use the following in your C++ files:

    #include <jgame3d/jgame3d.hpp>

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Compiling:

    You must include the following AT THE END OF your
compilation command:

    `jgame3d-flags`

For example:

    g++ -o b.out foo.cpp `jgame3d-flags`

    Note: For reasons I don't understand, this MUST MUST
MUST be at the END of your compilation command!

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The jtri.hpp file and its classes

    This file makes up the core of jgame3d. The basic
building block classes are as follows.

Point: A point in 3d space.

Triangle: A triangle in 3d space, made up of 3
    points.

Object: A associated group of triangles.

Camera: The rendering engine, holding a list of objects.

    All of the remaining classes are for internal
rendering and you don't need to worry about them.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The files.hpp file and saving models:

    The files.hpp file includes several methods for
saving and loading Model objects from files. Namely,
there is:

    saveModel(const Object &what, const char *where);

For saving Models (in a as-of-now exclusive format, i.e.
not compatible with anything else) to file, and the
function:

    loadModel(const char *where)

    For the inverse. I use .model as the file extension,
but it's basically plaintext so you can use whatever
extension your heart desires.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The text.hpp file and the Writer class:

    This file provides the Writer class, which is a
user-friendly wrapper for the SDL_ttf library. To start:

Writer writerObject(rend, "/usr/font.ttf", size);

    After instantiation, you can write using:

writerObject.write("text here", xPos, yPos, color);

    The first time a Writer renders a phrase will be
the most inefficient, as it must generate a new texture
with the phrase. From there, the texture will be stored
in memory and displaying it will be must cheaper.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
