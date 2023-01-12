#ifndef SCALING_HPP
#define SCALING_HPP

#include "basics.hpp"

// Scale a model about a point by a factor
void scaleBy(Model &m, const double by, const Point3D &about);

// Scale a polygon about a point by a factor
void scaleBy(Polygon &p, const double by, const Point3D &about);

#endif
