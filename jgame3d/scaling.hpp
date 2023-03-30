/*
Jordan "Jorb" Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2022 - present
GPLv3 held by author
*/

#ifndef SCALING_HPP
#define SCALING_HPP

#include "jtri.hpp"

// Scale a model about a point by a factor
void scaleBy(Object &m, const double by, const Point &about);

// Scale a polygon about a point by a factor
void scaleBy(Triangle &p, const double by, const Point &about);

#endif
