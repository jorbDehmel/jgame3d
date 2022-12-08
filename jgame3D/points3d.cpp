#include "points3d.hpp"
#include <cassert>

/////////////////////////////////////////

int FOV_SCALAR = 500;

Point3D globalHorizon(256, 256, 50);

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

Point3D operator*(const Point3D &a, const double b)
{
    Point3D out = a;
    out.x *= b;
    out.y *= b;
    out.z *= b;
    return out;
}

/////////////////////////////////////////

Polygon3D::Polygon3D(Point3D pointsIn[], int num)
{
    for (int i = 0; i < num; i++)
    {
        points.push_back(pointsIn[i]);
    }

    basis.x = basis.y = basis.z = 0;
    rotationX = 0;
    rotationY = 0;
    rotationZ = 0;
    return;
}

Polygon3D::Polygon3D(const Polygon3D &other)
{
    basis = other.basis;
    max = other.max;
    min = other.min;
    rotationX = other.rotationX;
    rotationY = other.rotationY;
    rotationZ = other.rotationZ;

    points.clear();
    for (auto p : other.points)
    {
        points.push_back(p);
    }
}

Polygon3D::Polygon3D()
{
    basis.x = basis.y = basis.z = 0;
    max = min = basis;
    points.clear();
    rotationX = rotationY = rotationZ = 0;
}

void Polygon3D::checkMinMax()
{
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

    return;
}

Polygon2D Polygon3D::project()
{
    assert(points.size() >= 1);

    checkMinMax();

    BasicPoint *out = new BasicPoint[points.size() + 1];

    for (int i = 0; i < points.size(); i++)
    {
        if (points[i].z < 0)
        {
            out[i].x = globalHorizon.x;
            out[i].y = globalHorizon.y;
            continue;
        }

        out[i].x = points[i].x - globalHorizon.x;
        out[i].y = points[i].y - globalHorizon.y;

        // Calculate
        out[i].x *= (FOV_SCALAR / points[i].z);
        out[i].y *= (FOV_SCALAR / points[i].z);

        out[i].x += globalHorizon.x;
        out[i].y += globalHorizon.y;
    }

    out[points.size()].x = out[0].x;
    out[points.size()].y = out[0].y;

    Polygon2D p(out, points.size());

    return p;
}

/////////////////////////////////////////

void Polygon3D::render(SDL_Renderer *renderer)
{
    if (basis.z > globalHorizon.z || basis.z < 0)
    {
        return;
    }

    Polygon3D temp = rotate(*this);
    temp = move(temp);

    temp.project().render(renderer);

    return;
}

void Polygon3D::renderCross(SDL_Renderer *renderer)
{
    if (basis.z > globalHorizon.z || basis.z < 0)
    {
        return;
    }

    Polygon3D temp = rotate(*this);
    temp = move(temp);

    temp.project().renderCross(renderer);

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
    Polygon3D out(p);

    // Rotate each point
    for (int i = 0; i < out.points.size(); i++)
    {
        rotatePoint(out.points[i], out.rotationX, out.rotationY, out.rotationZ);
    }

    // For some reason the basis doesn't copy over
    out.basis = p.basis;

    return out;
}

///////////////////////////////////////////////////////////////

void rotatePoint(Point3D &p, double dx = 0, double dy = 0, double dz = 0)
{
    double s = 0, c = 0;
    double x = p.x, y = p.y, z = p.z;

    // p.x = p.y = p.z = -1;

    // cout << "Rotations: " << dx << '\t' << dy << '\t' << dz << '\n';
    if (dx != 0)
    {
        s = sin(dx), c = cos(dx);
        assert(s == s);
        assert(c == c);

        x = p.x, y = p.y, z = p.z;

        p.y = (c * y) - (s * z);
        p.z = (s * y) + (c * z);
    }

    if (dy != 0)
    {
        s = sin(dy), c = cos(dy);
        assert(s == s);
        assert(c == c);

        x = p.x, y = p.y, z = p.z;

        p.x = (c * x) + (s * z);
        p.z = (s * -x) + (c * z);
    }

    if (dz != 0)
    {
        s = sin(dz), c = cos(dz);
        assert(s == s);
        assert(c == c);

        x = p.x, y = p.y, z = p.z;

        p.x = (c * x) - (s * y);
        p.y = (s * x) + (c * y);
    }

    // cout << "rotational output: " << p.x << '\t' << p.y << '\t' << p.z << '\n';

    return;
}

/////////////////////////////////////////
