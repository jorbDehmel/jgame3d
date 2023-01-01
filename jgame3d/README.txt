~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

jgame3d - Basic 3d game-building library for C++

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Jordan "Jorb" Dehmel, 2022 - 2023
jdehmel@outlook.com
github.com/jorbDehmel/jgame3d
also see github.com/jorbDehmel/jgame
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Installation:

    This library only supports Linux. It requires SDL2,
which will need to be required before this.

    To install this library, open this folder in
terminal and enter `make install`. From then on, you can
use the following in your C++ files:

    #include <jgame3d/jgame3d.hpp>

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Compiling:

    You must include /usr/include/jgame3d/bin/jgame3d.a
as the FINAL argument of your compilation command (this
file will be created upon running `make install`).

    This library depends of SDL2, and therefor you must
include the following in your compilation command:

    `sdl2-config --cflags --libs`

For example:

g++ `sdl2-config --cflags --libs` foo.cpp -o b.out \
    /usr/include/jgame3d/bin/jgame3d.a        

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Point3D, Polygon, and Model classes:

    The Point3D class represents a point in 3D space.
A Polygon is a collection of Point3D objects, as well as
an associated color. A Model is a colleciton of Polygons
(this is what is usually used for rendering).

    The move() and rotate() functions will work on the
later two classes and represent their respective 
transformations in 3D space. The fillPolygon() function
will fill a 2D polygon (represented by a vector of
Point3D objects) with a color.

    The getPointAtZBetween() function gets a point along
a line AB at a given z point.

    The projectPoint() function projects a 3D point into
2D space (namely the camera plane).

    The renderBetweenZ() function renders a sub-polygon
falling between two z positions.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Window class:

    The window class as defined in window.hpp is an
overlay for SDL2's sometimes clunky processes. At
instantiation, it initializes the needed SDL2 systems,
sets all rendering global variables as needed, makes a
Slicer object for rendering, and creates an SDL2 window.
Upon destruction, it closes the window, frees all
associated memory, and shuts down SDL2.

    Note: the function passed at instantiation as
"Update" will be called once per frame. It needs only
make changes to the positions, color, or amount of
added polygons. The actual clearing, rendering, timing,
and event handling will be handled by the Window class.
The return boolean from this will be used to determine
if the program should continue (true) or halt (false).

    The mainLoop method calls the Update function, then
renders all polygons. It then polls any keyboard events,
updates the mouse state and position globals, and delays
such that the frame update takes at minimum RefreshRate
milliseconds. It does this until the update function
returns false.

    The add methods insert a model or polygon into the
window's slicer's rendering order. The getter functions
getModels, getWindow, getSlicer, and getRenderer can all
be used to modify the internals of the Window for
rendering.

    The isKeyPressed method takes a key index and
returns whether or not that key is currently pressed.
The setUpScaleFactor method sets the upscaling of the
window (such that the rendering will occur at the
original resolution, but will be upscaled at display).

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The resources.hpp file:

    This file provides some useful functions. The color
namespace holds functions which return SDL_Color objects
representing their associated names. The createCube()
function creates a cube with its specified parameters.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Slicer class:

    This class is for internal use in the window class.
From a user's standpoint, you don't need to know about
this, but I spent a lot of time on it so I'm gonna put
it in the readme.

    This handles the rendering of polygons in the
context of 3D space. Any model on its list of models
will be broken down into its polygons upon calling
render(). These polygons will be sliced along the z axis
by increments of dz. These slices are then rendered from
furthest away to closest, such that any overlapping
polygons are rendered correctly according to their
z positions.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

License (via MIT)

Copyright © 2022 Jordan Dehmel

Permission is hereby granted, free of charge, to any 
person obtaining a copy of this software and associated 
documentation files (the “Software”), to deal in the 
Software without restriction, including without
limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice 
shall be included in all copies or substantial portions 
of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF 
ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED 
TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
SHALL  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN  CONNECTION WITH THE SOFTWARE OR THE USE
OR OTHER DEALINGS IN THE SOFTWARE.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
