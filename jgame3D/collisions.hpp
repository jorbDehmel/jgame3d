#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "points3d.hpp"

bool isPointWithin(const Point3D &p, const Polygon3D &poly);
bool isPointWithin(const Point3D &p, const Object &b);
bool isPolygonWithin(const Polygon3D &poly, const Object &obj);
bool isTouching(const Polygon3D &a, const Polygon3D &b);
bool isTouching(Object &a, Object &b);

#endif
