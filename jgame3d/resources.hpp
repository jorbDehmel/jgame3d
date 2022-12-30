#ifndef RESOURCES_H
#define RESOURCES_H

#include "basics.hpp"
#include "window.hpp"

namespace colors
{
    SDL_Color red();
    SDL_Color green();
    SDL_Color blue();

    SDL_Color black();
    SDL_Color grey();
    SDL_Color white();
};

void createCube(Model &obj, vector<SDL_Color> &colors);

#endif
