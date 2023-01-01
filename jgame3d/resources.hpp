#ifndef RESOURCES_H
#define RESOURCES_H

#include "basics.hpp"
#include "window.hpp"

// Functions returning SDL_Color objects of their names
namespace colors
{
    SDL_Color red();
    SDL_Color green();
    SDL_Color blue();

    SDL_Color black();
    SDL_Color grey();
    SDL_Color white();
};

// Create a cube with colors 'colors', and side length 'sideLength'
void createCube(Model &obj, vector<SDL_Color> &colors, double sideLength = 64);

void createSquare(Model &obj, SDL_Color color, double sideLength = 64);

#endif
