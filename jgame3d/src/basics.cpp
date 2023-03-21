/*
Jordan "Jorb" Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2022 - present
GPLv3 held by author
*/

#include "../basics.hpp"

//////////////////////////////

// Globals

int FOVScalar = 200;
Point3D horizon(100, 100, 100);

double dz = 1;
double dy = 1;

double renderMinX = 0, renderMinY = renderMinX;
double renderMaxX = 1000, renderMaxY = renderMaxX;
double renderMinZ = 0;
double renderMaxZ = 1028;

//////////////////////////////

SDL_Color makeColor(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
{
    SDL_Color out;
    out.r = r;
    out.g = g;
    out.b = b;
    out.a = a;
    return out;
}

//////////////////////////////

Point3D::Point3D()
{
    x = y = z = 0;
    return;
}

Point3D::Point3D(const Point3D &other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    return;
}

Point3D::Point3D(const double X, const double Y, const double Z)
{
    x = X;
    y = Y;
    z = Z;
    return;
}

bool operator==(const Point3D &a, const Point3D &b)
{
    return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
}

bool operator!=(const Point3D &a, const Point3D &b)
{
    return !(a == b);
}

//////////////////////////////

ostream &operator<<(ostream &stream, const Point3D &p)
{
    stream << "(" << p.x << '\t' << p.y << '\t' << p.z << ")";
    return stream;
}

ostream &operator<<(ostream &stream, const Polygon &p)
{
    stream << "Points:\n";

    for (Point3D p : p.points)
    {
        stream << p << '\n';
    }

    return stream;
}

ostream &operator<<(ostream &stream, const Model &p)
{
    stream << "Polygons:\n";

    for (Polygon poly : p.polygons)
    {
        stream << "\tPoints:\n";
        for (Point3D p : poly.points)
        {
            stream << "\t" << p << '\n';
        }
        stream << '\n';
    }

    return stream;
}

//////////////////////////////

Slicer::Slicer(SDL_Renderer *&Rend)
{
    rend = Rend;
    return;
}

void Slicer::render()
{
    vector<Polygon> polys;

    minZ = renderMaxZ;
    maxZ = renderMinZ;
    for (Model m : models)
    {
        if (!m.doRender)
        {
            continue;
        }

        for (Polygon p : m.polygons)
        {
            polys.push_back(p);

            // Move polygon such that absolute coordinates are maintained, but still align with camera junk
            move(polys.back(), cameraPos);
            rotate(polys.back(), Point3D(renderMaxX / 2, renderMaxY, 0), cameraRot);

            // Record min and max z values for later
            for (auto point : polys.back().points)
            {
                if (point.z < minZ)
                {
                    minZ = point.z;
                }
                if (point.z > maxZ)
                {
                    maxZ = point.z;
                }
            }
        }
    }

    if (polys.empty())
    {
        return;
    }

    if (mode == Normal)
    {
        double minBound, maxBound;

        maxBound = (renderMaxZ < maxZ) ? renderMaxZ : maxZ;
        minBound = (renderMinZ > minZ) ? renderMinZ : minZ;

        if (minBound < 0)
        {
            minBound = 0;
        }
        if (maxBound <= 0)
        {
            return;
        }

        // Standard iterative-z rendering
        for (double z = maxBound; z >= minBound; z -= dz)
        {
            for (Polygon poly : polys)
            {
                renderBetweenZ(rend, poly, z - dz, z + dz);
            }
        }
    }
    else if (mode == Wireframe)
    {
        for (Polygon poly : polys)
        {
            renderPolygon(rend, poly);
        }
    }

    return;
}

//////////////////////////////

Point3D getCenter(const Model &m)
{
    double minX, maxX, minY, maxY, minZ, maxZ;
    minX = maxX = m.polygons[0].points[0].x;
    minY = maxY = m.polygons[0].points[0].y;
    minZ = maxZ = m.polygons[0].points[0].z;

    for (auto poly : m.polygons)
    {
        for (auto point : poly.points)
        {
            if (point.x < minX)
                minX = point.x;
            else if (point.x > maxX)
                maxX = point.x;

            if (point.y < minY)
                minY = point.y;
            else if (point.y > maxY)
                maxY = point.y;

            if (point.z < minZ)
                minZ = point.z;
            else if (point.z > maxZ)
                maxZ = point.z;
        }
    }

    Point3D out;

    out.x = minX + ((maxX - minX) / 2);
    out.y = minY + ((maxY - minY) / 2);
    out.z = minZ + ((maxZ - minZ) / 2);

    return out;
}

Point3D getCenter(const Polygon &p)
{
    double minX, maxX, minY, maxY, minZ, maxZ;
    minX = maxX = p.points[0].x;
    minY = maxY = p.points[0].y;
    minZ = maxZ = p.points[0].z;

    for (auto point : p.points)
    {
        if (point.x < minX)
            minX = point.x;
        else if (point.x > maxX)
            maxX = point.x;

        if (point.y < minY)
            minY = point.y;
        else if (point.y > maxY)
            maxY = point.y;

        if (point.z < minZ)
            minZ = point.z;
        else if (point.z > maxZ)
            maxZ = point.z;
    }

    Point3D out;

    out.x = minX + ((maxX - minX) / 2);
    out.y = minY + ((maxY - minY) / 2);
    out.z = minZ + ((maxZ - minZ) / 2);

    return out;
}

//////////////////////////////

void move(Model &m, const Point3D &by)
{
    m.doRender = false;

    Point3D *current;
    for (int shapeNum = 0; shapeNum < m.polygons.size(); shapeNum++)
    {
        for (int pointNum = 0; pointNum < m.polygons[shapeNum].points.size(); pointNum++)
        {
            current = &m.polygons[shapeNum].points[pointNum];

            current->x += by.x;
            current->y += by.y;
            current->z += by.z;

            if (!m.doRender)
            {
                if (current->x > renderMinX && current->x < renderMaxX)
                {
                    if (current->y > renderMinY && current->y < renderMaxY)
                    {
                        if (current->z > renderMinZ && current->z < renderMaxZ)
                        {
                            m.doRender = true;
                        }
                    }
                }
            }
        }
    }
    return;
}

void rotate(Model &m, const Point3D &about, const Rotation &by)
{
    for (int shapeNum = 0; shapeNum < m.polygons.size(); shapeNum++)
    {
        rotate(m.polygons[shapeNum], about, by);
    }
    return;
}

void rotate(Model &m, const Rotation &by)
{
    rotate(m, getCenter(m), by);
    return;
}

void move(Polygon &p, const Point3D &by)
{
    for (int pointNum = 0; pointNum < p.points.size(); pointNum++)
    {
        p.points[pointNum].x += by.x;
        p.points[pointNum].y += by.y;
        p.points[pointNum].z += by.z;
    }
    return;
}

void rotate(Polygon &p, const Point3D &about, const Rotation &by)
{
    Point3D *current;
    for (int pointNum = 0; pointNum < p.points.size(); pointNum++)
    {
        current = &p.points[pointNum];

        current->x -= about.x;
        current->y -= about.y;
        current->z -= about.z;

        rotate(*current, by);

        current->x += about.x;
        current->y += about.y;
        current->z += about.z;
    }
    return;
}

void rotate(Polygon &m, const Rotation &by)
{
    rotate(m, getCenter(m), by);
    return;
}

void rotate(Point3D &p, const Rotation &by)
{
    double s = 0, c = 0;
    double x = p.x, y = p.y, z = p.z;

    if (by.x != 0)
    {
        s = SDL_sinf(by.x), c = SDL_cosf(by.x);
        x = p.x, y = p.y, z = p.z;

        p.y = (c * y) - (s * z);
        p.z = (s * y) + (c * z);
    }

    if (by.y != 0)
    {
        s = SDL_sinf(by.y), c = SDL_cosf(by.y);
        x = p.x, y = p.y, z = p.z;

        p.x = (c * x) + (s * z);
        p.z = (s * -x) + (c * z);
    }

    if (by.z != 0)
    {
        s = SDL_sinf(by.z), c = SDL_cosf(by.z);
        x = p.x, y = p.y, z = p.z;

        p.x = (c * x) - (s * y);
        p.y = (s * x) + (c * y);
    }

    return;
}

//////////////////////////////

void fillPolygon(SDL_Renderer *rend, vector<SDL_FPoint> &poly, SDL_Color color)
{
    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);

    double X1, X2, Y1, Y2;
    vector<double> xValues;

    double yMin = poly[0].y, yMax = yMin;
    for (SDL_FPoint p : poly)
    {
        if (p.y < yMin)
            yMin = p.y;
        else if (p.y > yMax)
            yMax = p.y;
    }

    for (double y = yMin; y < yMax; y += dy)
    {
        if (y < renderMinY)
            continue;
        else if (y > renderMaxY)
            break;

        xValues.clear();
        for (int i = 0; i < poly.size(); i++)
        {
            X1 = poly[i].x;
            Y1 = poly[i].y;
            X2 = poly[(i + 1) % (poly.size())].x;
            Y2 = poly[(i + 1) % (poly.size())].y;

            if (Y1 < y && Y2 < y)
                continue;
            else if (Y1 > y && Y2 > y)
                continue;

            // curY * (dx/dy) - y1 * (dx/dy) + x1
            xValues.push_back(y * ((X2 - X1) / (Y2 - Y1)) - Y1 * ((X2 - X1) / (Y2 - Y1)) + X1);
        }

        if (xValues.size() <= 1)
            continue;

        sort(xValues.begin(), xValues.end());

        // Draw line segments
        for (int i = 0; i < xValues.size(); i += 2)
        {
            SDL_RenderDrawLineF(rend, xValues[i], y, xValues[(i + 1) % (xValues.size())], y);
        }
    }

    return;
}

//////////////////////////////

Point3D getPointAtZBetween(const Point3D &A, const Point3D &B, double z)
{
    Point3D out;
    out.z = z;

    if (A.z == B.z)
    {
        // Equivolence
        out.x = A.x;
        out.y = A.y;
    }
    else
    {
        // Compute coords for out (along line)
        if (B.x == A.x)
            out.x = A.x;
        else
            out.x = z * ((B.x - A.x) / (B.z - A.z)) - A.z * ((B.x - A.x) / (B.z - A.z)) + A.x;

        if (B.y == A.y)
            out.y = A.y;
        else
            out.y = z * ((B.y - A.y) / (B.z - A.z)) - A.z * ((B.y - A.y) / (B.z - A.z)) + A.y;
    }

    return out;
}

SDL_FPoint projectPoint(const Point3D &p)
{
    if (p.z == 0)
        return SDL_FPoint{0.0, 0.0};

    SDL_FPoint out;
    out.x = p.x;
    out.y = p.y;

    // Project onto plane via z-coord
    out.x -= horizon.x;
    out.y -= horizon.y;

    out.x *= (FOVScalar / p.z);
    out.y *= (FOVScalar / p.z);

    out.x += horizon.x;
    out.y += horizon.y;

    return out;
}

void renderBetweenZ(SDL_Renderer *rend, Polygon &p, double z1, double z2)
{
    if (p.points.empty())
        return;

    vector<SDL_FPoint> points;

    // Make z1 < z2
    if (z1 > z2)
    {
        double temp = z1;
        z1 = z2;
        z2 = temp;
    }

    for (int i = 0; i < p.points.size(); i++)
    {
        Point3D prev = p.points[(i - 1) % (p.points.size())];
        Point3D cur = p.points[i];
        Point3D next = p.points[(i + 1) % (p.points.size())];

        if (cur.z < z1 && next.z < z1 && prev.z < z1)
        {
            continue;
        }
        else if (cur.z > z2 && next.z > z2 && prev.z > z2)
        {
            continue;
        }

        if (cur.z < z1)
        {
            if (prev.z >= z1)
            {
                points.push_back(projectPoint(getPointAtZBetween(cur, prev, z1)));
            }
            if (next.z >= z1)
            {
                points.push_back(projectPoint(getPointAtZBetween(cur, next, z1)));
            }
        }
        else if (cur.z > z2)
        {
            if (prev.z <= z2)
            {
                points.push_back(projectPoint(getPointAtZBetween(cur, prev, z2)));
            }
            if (next.z <= z2)
            {
                points.push_back(projectPoint(getPointAtZBetween(cur, next, z2)));
            }
        }
        else
        {
            points.push_back(projectPoint(cur));
        }
    }

    if (!points.empty())
    {
        fillPolygon(rend, points, p.color);
    }

    return;
}

//////////////////////////////

void renderPolygon(SDL_Renderer *rend, Polygon &p)
{
    SDL_FPoint *points = new SDL_FPoint[p.points.size() + 1];

    for (int i = 0; i < p.points.size(); i++)
    {
        points[i] = projectPoint(p.points[i]);
    }
    points[p.points.size()] = points[0];

    SDL_SetRenderDrawColor(rend, p.color.r, p.color.g, p.color.b, p.color.a);
    SDL_RenderDrawLinesF(rend, points, p.points.size() + 1);

    delete[] points;

    return;
}

//////////////////////////////
