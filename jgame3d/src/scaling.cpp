#include "../scaling.hpp"

void scaleBy(Model &m, const double by, const Point3D &about)
{
    for (int i = 0; i < m.polygons.size(); i++)
    {
        scaleBy(m.polygons[i], by, about);
    }

    return;
}

void scaleBy(Polygon &p, const double by, const Point3D &about)
{
    for (int i = 0; i < p.points.size(); i++)
    {
        Point3D newPoint = p.points[i];

        newPoint.x -= about.x, newPoint.y -= about.y, newPoint.z -= about.z;
        newPoint.x *= by, newPoint.y *= by, newPoint.z *= by;
        newPoint.x += about.x, newPoint.y += about.y, newPoint.z += about.z;

        p.points[i] = newPoint;
    }

    return;
}
