#ifndef TEXTURES_H
#define TEXTURES_H

#include "objects.hpp"

////////////////////////////////////

// Object wrapper with textures
struct Sprite3D
{
public:
    Sprite3D(Object &o, vector<SDL_Surface *> &t);
    ~Sprite3D();

    Object obj;
    vector<SDL_Surface *> textures;
};

void fillPolygon(SDL_Renderer *rend, Polygon2D &p, const unsigned int color);
void fillPolygon(SDL_Renderer *rend, Polygon3D &p, const unsigned int color, Point3D horizon); // This MUST run in order(n)!

void mapSurface(SDL_Renderer *rend, const SDL_Surface *surface, const Polygon2D &p);
void mapSurface(SDL_Renderer *rend, const SDL_Surface *surface, const Polygon3D &p);

void textureObject(SDL_Renderer *rend, const Object &obj);

////////////////////////////////////

#endif
