#ifndef POINTS3D_H
#define POINTS3D_H

#include "points.hpp"

/////////////////////////////////////////

class Point3D
{
public:
    Point3D() {}
    Point3D(double xIn, double yIn, double zIn) : x(xIn), y(yIn), z(zIn) {}
    double x, y, z;
};

/////////////////////////////////////////

class Polygon3D
{
public:
    Polygon3D(Point3D pointsIn[], int num);
    SDL_FPoint *SDLify();

    void operator+=(Polygon3D &other);

    double rotationX, rotationY, rotationZ;
    Point3D basis;
    vector<Point3D> points;
};

/////////////////////////////////////////

int SDL_RenderDrawLinesF(SDL_Renderer *renderer, Polygon3D &polygon);
void move(Polygon3D &poly, Point3D by);
void rotate(Polygon3D &poly, double dx, double dy, double dz);
void rotatePoint(Point3D &p, double dx, double dy, double dz);

/////////////////////////////////////////

#endif
