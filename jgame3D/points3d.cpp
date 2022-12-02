#include "points3d.hpp"

/////////////////////////////////////////

int FOV_SCALAR = 1;
int Z_CUTOFF_SCALAR = 100;

/////////////////////////////////////////

Point3D operator+(const Point3D &a, const Point3D &b)
{
    Point3D out = a;
    out.x += b.x;
    out.y += b.y;
    out.z += b.z;
    return out;
}

Point3D operator-(const Point3D &a, const Point3D &b)
{
    Point3D out = a;
    out.x -= b.x;
    out.y -= b.y;
    out.z -= b.z;
    return out;
}

/////////////////////////////////////////

Polygon3D::Polygon3D(Point3D pointsIn[], int num)
{
    for (int i = 0; i < num; i++)
    {
        points.push_back(pointsIn[i]);
    }
    return;
}

SDL_FPoint *Polygon3D::SDLify(Point3D &horizon)
{
    assert(points.size() >= 1);

    min = max = points[0];
    for (Point3D p : points)
    {
        if (p.x < min.x)
            min.x = p.x;
        if (p.x > max.x)
            max.x = p.x;
        if (p.y < min.y)
            min.y = p.y;
        if (p.y > max.y)
            max.y = p.y;
        if (p.z < min.z)
            min.z = p.z;
        if (p.z > max.z)
            max.z = p.z;
    }

    SDL_FPoint *out = new SDL_FPoint[points.size() + 1];

    for (int i = 0; i < points.size(); i++)
    {
        out[i].x = points[i].x - horizon.x;
        out[i].y = points[i].y - horizon.y;

        // Calculate
        out[i].x *= 1 + (horizon.z / (points[i].z * FOV_SCALAR));
        out[i].y *= 1 + (horizon.z / (points[i].z * FOV_SCALAR));

        out[i].x += horizon.x;
        out[i].y += horizon.y;
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

void Polygon3D::render(SDL_Renderer *renderer, Point3D &horizon)
{
    cout << "Polygon render called\n";

    if (basis.z > (horizon.z * Z_CUTOFF_SCALAR) || basis.z < 0)
    {
        return;
    }

    Polygon3D temp = rotate(*this);
    temp = move(temp);

    SDL_RenderDrawLinesF(renderer, temp.SDLify(horizon), temp.points.size() + 1);

    return;
}

void Polygon3D::renderCross(SDL_Renderer *renderer, Point3D &horizon)
{
    if (basis.z > (horizon.z * Z_CUTOFF_SCALAR) || basis.z < 0)
    {
        return;
    }

    Polygon3D temp = rotate(*this);
    temp = move(temp);

    SDL_FPoint a, b;
    auto points = temp.SDLify(horizon);

    for (int i = 0; i < temp.points.size(); i++)
    {
        for (int j = i; j < temp.points.size(); j++)
        {
            a.x = points[i].x;
            a.y = points[i].y;

            b.x = points[j].x;
            b.y = points[j].y;

            SDL_RenderDrawLineF(renderer, a.x, a.y, b.x, b.y);
        }
    }
    return;
}

///////////////////////////////////////////////////////////////

Polygon3D move(const Polygon3D poly)
{
    Polygon3D out = poly;
    for (int i = 0; i < out.points.size(); i++)
    {
        out.points[i].x += poly.basis.x;
        out.points[i].y += poly.basis.y;
        out.points[i].z += poly.basis.z;
    }
    return out;
}

Polygon3D rotate(const Polygon3D p)
{
    Polygon3D out = p;

    out.basis.x = 0;
    out.basis.y = 0;
    out.basis.z = 0;
    out = move(out);

    for (int i = 0; i < out.points.size(); i++)
    {
        rotatePoint(out.points[i], out.rotationX, out.rotationY, out.rotationZ);
    }

    out.basis = p.basis;
    out = move(out);

    return out;
}

///////////////////////////////////////////////////////////////

void rotatePoint(Point3D &p, double dx = 0, double dy = 0, double dz = 0)
{
    double s, c;
    double x, y, z;

    if (dx != 0)
    {
        s = sin(dx), c = cos(dx);
        x = p.x, y = p.y, z = p.z;

        p.y = (c * y) - (s * z);
        p.z = (s * y) + (c * z);
    }

    if (dy != 0)
    {
        s = sin(dy), c = cos(dy);
        x = p.x, y = p.y, z = p.z;

        p.x = (c * x) + (s * z);
        p.z = (s * -x) + (c * z);
    }

    if (dz != 0)
    {
        s = sin(dz), c = cos(dz);
        x = p.x, y = p.y, z = p.z;

        p.x = (c * x) - (s * y);
        p.y = (s * x) + (c * y);
    }

    return;
}

/////////////////////////////////////////
