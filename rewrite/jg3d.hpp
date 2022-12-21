#ifndef JG3D2_H
#define JG3D2_H

#include <cassert>
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
using namespace std;

class Point3D
{
public:
    Point3D();
    Point3D(const Point3D &other);
    Point3D(const double x, const double y, const double z);

    double x, y, z;
};

typedef Point3D Rotation;

extern int FOV_SCALAR;
extern Point3D horizon;

class Polygon
{
public:
    Point3D posOffset;
    Rotation rotOffset;

    vector<Point3D> points;
    SDL_Color color;
};

class Model
{
public:
    vector<Polygon> polygons;
};

class Renderer
{
public:
    Renderer(SDL_Renderer *&rend, SDL_Window *&wind);

    void render();

    vector<Model *> models;

    SDL_Renderer *rend;
    SDL_Window *wind;
};

void move(Model m, const Point3D &by);
void rotate(Model m, const Point3D &about, const Rotation &by);

void move(Polygon m, const Point3D &by);
void rotate(Polygon m, const Point3D &about, const Rotation &by);

void rotate(Point3D &p, const Rotation &by);

#endif
