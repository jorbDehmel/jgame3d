#ifndef TEXTURES_H
#define TEXTURES_H

#include "objects.hpp"
#include <algorithm>

////////////////////////////////////

extern int X_RENDER_THRESH, Y_RENDER_THRESH;

////////////////////////////////////

void fillPolygon(SDL_Renderer *rend, Polygon2D &p, Pixel color);
void fillPolygon(SDL_Renderer *rend, Polygon3D &p, Pixel color);

////////////////////////////////////

#endif
