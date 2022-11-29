#include "points3d.hpp"

/////////////////////////////////////////

#define GUI_SCALAR 1000
const Point3D horizon(256, 256, 512);

/////////////////////////////////////////

Polygon3D::Polygon3D(Point3D pointsIn[], int num)
{
    for (int i = 0; i < num; i++)
    {
        points.push_back(pointsIn[i]);
    }
    return;
}

SDL_FPoint *Polygon3D::SDLify()
{
    assert(points.size() >= 1);

    SDL_FPoint *out = new SDL_FPoint[points.size() + 1];

    double x, y;
    double scalar;
    for (int i = 0; i < points.size(); i++)
    {
        // Calculate
        x = points[i].x;
        y = points[i].y;

        // Scale via z here
        scalar = (GUI_SCALAR / (points[i].z + GUI_SCALAR));

        x = ((x - horizon.x) * scalar) + horizon.x;
        y = ((y - horizon.y) * scalar) + horizon.y;

        // Set to point
        out[i].x = x;
        out[i].y = y;
    }
    out[points.size()].x = out[0].x;
    out[points.size()].y = out[0].y;

    return out;
}

void Polygon3D::operator+=(Polygon3D &other)
{
    for (auto point : other.points)
    {
        points.push_back(point);
    }
    return;
}

/////////////////////////////////////////

int SDL_RenderDrawLinesF(SDL_Renderer *renderer, Polygon3D &polygon)
{
    if (polygon.basis.z > horizon.z)
    {
        return 0;
    }

    Polygon3D temp(polygon);
    rotate(temp, polygon.rotationX, polygon.rotationY, polygon.rotationZ);
    move(temp, polygon.basis);

    return SDL_RenderDrawLinesF(renderer, temp.SDLify(), temp.points.size() + 1);
}

void move(Polygon3D &poly, Point3D by)
{
    for (int i = 0; i < poly.points.size(); i++)
    {
        poly.points[i].x += by.x;
        poly.points[i].y += by.y;
        poly.points[i].z += by.z;
    }
    return;
}

void rotate(Polygon3D &p, double dx, double dy, double dz)
{
    Point3D about = p.points[0];
    move(p, Point3D(-about.x, -about.y, -about.z));

    for (int i = 0; i < p.points.size(); i++)
    {
        rotatePoint(p.points[i], dx, dy, dz);
    }

    move(p, about);

    return;
}

void rotatePoint(Point3D &p, double dx, double dy, double dz)
{

    if (dx != 0)
    {
        double sx = sin(dx), cx = cos(dx);

        p.y = (cx * p.y) - (sx * p.z);
        p.z = (sx * p.y) + (cx * p.z);
    }

    if (dy != 0)
    {
        double sy = sin(dy), cy = cos(dy);

        p.x = (cy * p.x) + (sy * p.z);
        p.z = -(sy * p.x) + (cy * p.z);
    }

    if (dz != 0)
    {
        double sz = sin(dz), cz = cos(dz);

        p.x = (cz * p.x) - (sz * p.y);
        p.y = (sz * p.x) + (cz * p.y);
    }

    return;
}

/////////////////////////////////////////
