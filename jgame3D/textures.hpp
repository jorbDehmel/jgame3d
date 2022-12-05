#ifndef TEXTURES_H
#define TEXTURES_H

#include "objects.hpp"

////////////////////////////////////

void fillPolygon(SDL_Renderer *rend, Polygon2D &p, const unsigned int color);
void fillPolygon(SDL_Renderer *rend, Polygon3D &p, const unsigned int color, Point3D horizon); // This MUST run in order(n)!

void mapSurface(SDL_Renderer *rend, const SDL_Surface *surface, const Polygon2D &p);
void mapSurface(SDL_Renderer *rend, const SDL_Surface *surface, const Polygon3D &p);

////////////////////////////////////

#endif
