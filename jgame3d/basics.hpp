/*
Jordan "Jorb" Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2022 - present
GPLv3 held by author
*/

#ifndef BASICS_H
#define BASICS_H

#include <SDL2/SDL.h>

#include <iostream>

#include <cassert>
#include <algorithm>
#include <chrono>

#include <map>
#include <vector>

using namespace std;

//////////////////////////////

// Create an SDL_Color instance with the given rgba values
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

    Point3D operator=(const Point3D &other)
    {
        x = other.x, y = other.y, z = other.z;
        return other;
    }

    void operator+=(const Point3D &other)
    {
        x += other.x, y += other.y, z += other.z;
        return;
    }

    double x, y, z;
};

bool operator==(const Point3D &a, const Point3D &b);
bool operator!=(const Point3D &a, const Point3D &b);

// Insert the coordinated of the Point3D object into the stream and return
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

// Change in z for layered rendering
extern double dz;

// Change in y for filling polygons
extern double dy;

// The min and max coordinates to render
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

// Insert the points in a polygon into a stream and return
ostream &operator<<(ostream &stream, const Polygon &p);

/*
A model in 3D space, holding a vector of Polygons
*/
class Model
{
public:
    vector<Polygon> polygons;
    bool doRender = true;
};

// Insert the polygons in a model into a stream and return
ostream &operator<<(ostream &stream, const Model &p);

//////////////////////////////

enum SlicerModes
{
    Normal,
    Wireframe,
    Experimental,
};

/*
A slicing renderer for proper layering in space.
Handles overlapping polygons.
*/
class Slicer
{
public:
    Slicer(SDL_Renderer *&rend);

    void render();

    vector<Model> models;

    SDL_Renderer *rend;

    Point3D cameraPos;
    Rotation cameraRot;

    SlicerModes mode = Normal;

protected:
    Point3D oldCameraPos;
    Rotation oldCameraRot;

    double minZ = 10000, maxZ = -10000;
};

//////////////////////////////

// Get the center point of a Model object
Point3D getCenter(const Model &m);

// Get the center point of a Polygon object
Point3D getCenter(const Polygon &m);

// Mode a model by a point
void move(Model &m, const Point3D &by);

// Rotate a model about a point and by a rotation
void rotate(Model &m, const Point3D &about, const Rotation &by);

// Rotate a Model about its center by a rotation
void rotate(Model &m, const Rotation &by);

// Mode a polygon by a point
void move(Polygon &m, const Point3D &by);

// Rotate a polygon about a point and by a rotation
void rotate(Polygon &m, const Point3D &about, const Rotation &by);

// Rotate a polygon about its center by a rotation
void rotate(Polygon &m, const Rotation &by);

// Rotate a point by a rotation
void rotate(Point3D &p, const Rotation &by);

// Fill a 2D polygon with a color
void fillPolygon(SDL_Renderer *rend, vector<SDL_FPoint> &poly, SDL_Color color);

// Wire a polygon wireframe
void renderPolygon(SDL_Renderer *rend, Polygon &p);

//////////////////////////////

// Get the point along the line AB which has the given z value (for internal rendering)
Point3D getPointAtZBetween(const Point3D &A, const Point3D &B, double z);

// Project a point in 3D space onto the camera-plane (in 2D space) (for internal rendering)
SDL_FPoint projectPoint(const Point3D &p);

// Render only the sub-polygon which falls between z1 and z2 (for internal rendering)
void renderBetweenZ(SDL_Renderer *rend, Polygon &p, double z1, double z2);

//////////////////////////////

#endif
