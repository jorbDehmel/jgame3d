#ifndef BASICS_H
#define BASICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_test_font.h>

#include <cassert>
#include <iostream>
#include <algorithm>
#include <chrono>

#include <map>
#include <vector>
// #include <set>

using namespace std;

//////////////////////////////

SDL_Color makeColor(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a);

/*
A point in 3D space
(Coords are held by doubles)
*/
class Point3D
{
public:
    Point3D();
    Point3D(const Point3D &other);
    Point3D(const double x, const double y, const double z);

    double x, y, z;
};

ostream &operator<<(ostream &stream, const Point3D &p);

/*
A rotation in 3D space
x, y, and z represent rotations in their
respective axiis
*/
typedef Point3D Rotation;

//////////////////////////////

// Adjusts FOV, akin to fisheye
extern int FOVScalar;

// Global horizon point used by rendering
extern Point3D horizon;

// Change in z and y for layered rendering
extern double dz, dy;

extern double renderMinZ, renderMaxZ, renderMinY, renderMaxY, renderMinX, renderMaxX;

//////////////////////////////

/*
A polygon, holding a vector of points in 3D space.
*/
class Polygon
{
public:
    vector<Point3D> points;
    SDL_Color color;
};

ostream &operator<<(ostream &stream, const Polygon &p);

/*
A model in 3D space, holding a vector of Polygons
*/
class Model
{
public:
    vector<Polygon> polygons;
};

ostream &operator<<(ostream &stream, const Model &p);

//////////////////////////////

/*
A renderer for proper layering in space.
Without this, things will only display in render order,
but with this they are able to overlap eachother.
*/
class Renderer
{
public:
    Renderer(SDL_Renderer *&rend, SDL_Window *&wind);

    void render();

    vector<Model> models;

    SDL_Renderer *rend;
    SDL_Window *wind;
};

//////////////////////////////

// Get the center point of a model in 3D
Point3D getCenter(const Model &m);
Point3D getCenter(const Polygon &m);

// Mode a model by a point
void move(Model &m, const Point3D &by);

// Rotate a model about a point and by a rotation
void rotate(Model &m, const Point3D &about, const Rotation &by);
void rotate(Model &m, const Rotation &by);

// Mode a polygon by a point
void move(Polygon &m, const Point3D &by);

// Rotate a polygon about a point and by a rotation
void rotate(Polygon &m, const Point3D &about, const Rotation &by);
void rotate(Polygon &m, const Rotation &by);

// Rotate a point by a rotation
void rotate(Point3D &p, const Rotation &by);

// Fill a 2D polygon with a color
void fillPolygon(SDL_Renderer *rend, vector<SDL_FPoint> &poly, SDL_Color color);

//////////////////////////////

#endif
