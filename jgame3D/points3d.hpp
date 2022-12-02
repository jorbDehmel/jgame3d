#ifndef POINTS3D_H
#define POINTS3D_H

#include "points.hpp"

/////////////////////////////////////////

class Point3D
{
public:
    Point3D() {}
    Point3D(double xIn, double yIn, double zIn) : x(xIn), y(yIn), z(zIn) {}

    Point3D operator=(Point3D other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }
    double x, y, z;
};

Point3D operator+(const Point3D &a, const Point3D &b);
Point3D operator-(const Point3D &a, const Point3D &b);

/////////////////////////////////////////

class Polygon3D
{
public:
    Polygon3D() {}
    Polygon3D(Point3D pointsIn[], int num);

    SDL_FPoint *SDLify(Point3D &horizon);
    void operator+=(Polygon3D &other);
    void render(SDL_Renderer *rend, Point3D &horizon);
    void renderCross(SDL_Renderer *rend, Point3D &horizon);

    double rotationX, rotationY, rotationZ;
    Point3D basis, min, max;

    vector<Point3D> points;
};

/////////////////////////////////////////

Polygon3D move(const Polygon3D poly);
Polygon3D rotate(const Polygon3D poly);

void rotatePoint(Point3D &p, double dx, double dy, double dz);

/////////////////////////////////////////

#endif
