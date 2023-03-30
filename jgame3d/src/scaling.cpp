/*
Jordan "Jorb" Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2022 - present
GPLv3 held by author
*/

#include "../scaling.hpp"

void scaleBy(Object &m, const double by, const Point &about)
{
    for (int i = 0; i < m.triangles.size(); i++)
    {
        scaleBy(m.triangles[i], by, about);
    }

    return;
}

Point scalePoint(const Point &What, const double &By, const Point &About)
{
    Point out = What;

    out.x -= About.x;
    out.y -= About.y;
    out.z -= About.z;

    out.x *= By;
    out.y *= By;
    out.z *= By;

    out.x += About.x;
    out.y += About.y;
    out.z += About.z;

    return out;
}

void scaleBy(Triangle &p, const double by, const Point &about)
{
    p.a = scalePoint(p.a, by, about);
    p.b = scalePoint(p.b, by, about);
    p.c = scalePoint(p.c, by, about);

    return;
}
