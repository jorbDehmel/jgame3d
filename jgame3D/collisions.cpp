#include "collisions.hpp"

bool isPointWithin(const Point3D &p, const Polygon3D &poly)
{
    Polygon3D temp = move(rotate(poly));

    double minX, maxX, minY, maxY, minZ, maxZ;
    minX = maxX = temp.points[0].x;
    minY = maxY = temp.points[0].y;
    minZ = maxZ = temp.points[0].z;

    for (Point3D point : temp.points)
    {
        if (point.x < minX)
        {
            minX = point.x;
        }

        if (point.x > maxX)
        {
            minX = point.x;
        }

        if (point.y < minY)
        {
            minY = point.y;
        }

        if (point.y > maxY)
        {
            minY = point.y;
        }

        if (point.z < minZ)
        {
            minZ = point.z;
        }

        if (point.z > maxZ)
        {
            minZ = point.z;
        }
    }

    return (p.x >= minX && p.x <= maxX) && (p.y >= minY && p.y <= maxY) && (p.z >= minZ && p.z <= maxZ);
}

bool isTouching(const Polygon3D &a, const Polygon3D &b)
{
    for (int i = 0; i < a.points.size(); i++)
    {
        if (isPointWithin(a.points[i], b))
        {
            return true;
        }
    }
    for (int i = 0; i < b.points.size(); i++)
    {
        if (isPointWithin(b.points[i], a))
        {
            return true;
        }
    }
    return false;
}

bool isPointWithin(const Point3D &p, const Object &b)
{
    Object temp = b;

    return (p.x >= temp.min.x && p.x <= temp.max.x) && (p.y >= temp.min.y && p.y <= temp.max.y) && (p.z >= temp.min.z && p.z <= temp.max.z);
}

bool isPolygonWithin(const Polygon3D &poly, const Object &obj)
{
    Object temp = obj;

    double minX, maxX, minY, maxY, minZ, maxZ;
    minX = maxX = temp.shapes[0].points[0].x;
    minY = maxY = temp.shapes[0].points[0].y;
    minZ = maxZ = temp.shapes[0].points[0].z;

    for (Polygon3D shape : temp.shapes)
    {
        for (Point3D point : shape.points)
        {
            if (point.x < minX)
            {
                minX = point.x;
            }

            if (point.x > maxX)
            {
                minX = point.x;
            }

            if (point.y < minY)
            {
                minY = point.y;
            }

            if (point.y > maxY)
            {
                minY = point.y;
            }

            if (point.z < minZ)
            {
                minZ = point.z;
            }

            if (point.z > maxZ)
            {
                minZ = point.z;
            }
        }
    }

    for (Point3D p : poly.points)
    {
        if ((p.x >= minX && p.x <= maxX) && (p.y >= minY && p.y <= maxY) && (p.z >= minZ && p.z <= maxZ))
        {
            return true;
        }
    }
    return false;
}

bool isTouching(const Object &a, const Object &b)
{
    for (Polygon3D p : a.shapes)
    {
        if (isPolygonWithin(p, b))
        {
            return true;
        }
    }
    for (Polygon3D p : b.shapes)
    {
        if (isPolygonWithin(p, a))
        {
            return true;
        }
    }
    return false;
}
