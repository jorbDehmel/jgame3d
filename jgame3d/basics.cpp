#include "basics.hpp"

//////////////////////////////

int FOVScalar = 200;
Point3D horizon(100, 100, 100);

double dz = 1;
double dy = 1;

double renderMinX = 0, renderMinY = renderMinX;
double renderMaxX = 512, renderMaxY = renderMaxX;
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
}

Point3D::Point3D(const Point3D &other)
{
    x = other.x;
    y = other.y;
    z = other.z;
}

Point3D::Point3D(const double X, const double Y, const double Z)
{
    x = X;
    y = Y;
    z = Z;
}

ostream &operator<<(ostream &stream, const Point3D &p)
{
    stream << "(" << p.x << '\t' << p.y << '\t' << p.z << ")";
    return stream;
}

//////////////////////////////

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

Renderer::Renderer(SDL_Renderer *&Rend, SDL_Window *&Wind)
{
    rend = Rend;
    wind = Wind;
}

Point3D getPointAtZBetween(const Point3D &A, const Point3D &B, double z)
{
    Point3D out;
    out.z = z;

    // Compute coords for out (along line)
    out.x = z * ((B.x - A.x) / (B.z - A.z)) - A.z * ((B.x - A.x) / (B.z - A.z)) + A.x;
    out.y = z * ((B.y - A.y) / (B.z - A.z)) - A.z * ((B.y - A.y) / (B.z - A.z)) + A.y;

    return out;
}

SDL_FPoint projectPoint(const Point3D &p)
{
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

void renderBetweenZ(SDL_Renderer *rend, Polygon &p, const double z1, const double z2)
{
    vector<SDL_FPoint> points;

    for (int i = 0; i < p.points.size(); i++)
    {
        Point3D a = p.points[i];
        Point3D b = p.points[(i + 1) % (p.points.size())];

        // Make a.z less than b.z
        if (a.z > b.z)
        {
            Point3D temp = a;
            a = b;
            b = temp;
        }

        // If line is before z1, continue
        if (a.z < z1 && b.z < z1)
            continue;

        // If line is after z2, continue
        else if (a.z > z2 && b.z > z2)
            continue;

        // If line is between z points, don't do anything
        else if (a.z >= z1 && a.z <= z2 && b.z >= z1 && b.z <= z2)
        {
            points.push_back(projectPoint(a));
        }

        else
        {
            // If passes through z1, fix
            if (a.z < z1 && b.z > z1)
            {
                points.push_back(projectPoint(getPointAtZBetween(a, b, z1)));
            }
            // If passes through z2, fix
            if (a.z < z2 && b.z > z2)
            {
                points.push_back(projectPoint(getPointAtZBetween(a, b, z2)));
            }
        }
    } // End iterating over points

    if (!points.empty())
    {
        //cout << "Points: (color " << (int)p.color.r << ' ' << (int)p.color.g << ' ' << (int)p.color.b << ' ' << (int)p.color.a << ")\n";
        //for (auto p : points)
        //    cout << p.x << '\t' << p.y << '\n';
        //cout << '\n';

        fillPolygon(rend, points, p.color);
    }

    return;
}

void Renderer::render()
{
    // Prepare min and max
    vector<Polygon> polys;

    vector<double> zBreakPoints;
    zBreakPoints.push_back(renderMinZ);
    zBreakPoints.push_back(renderMaxZ);

    for (Model *m : models)
    {
        for (Polygon p : m->polygons)
        {
            polys.push_back(p);

            for (Point3D point : p.points)
            {
                if (find(zBreakPoints.begin(), zBreakPoints.end(), point.z) == zBreakPoints.end())
                {
                    zBreakPoints.push_back(point.z);
                    zBreakPoints.push_back(point.z);
                }
            }
        }
    }

    sort(zBreakPoints.begin(), zBreakPoints.end());

    for (int i = zBreakPoints.size() - 1; i > 0; i--)
    {
        // cout << "Rendering between z " << zBreakPoints[i] << " and " << zBreakPoints[i - 1] << '\n';

        // Iterate over
        for (int polygonIndex = 0; polygonIndex < polys.size(); polygonIndex++)
        {
            renderBetweenZ(rend, polys[polygonIndex], zBreakPoints[i], zBreakPoints[i - 1]);
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
    Point3D *current;
    for (int shapeNum = 0; shapeNum < m.polygons.size(); shapeNum++)
    {
        for (int pointNum = 0; pointNum < m.polygons[shapeNum].points.size(); pointNum++)
        {
            current = &m.polygons[shapeNum].points[pointNum];

            current->x += by.x;
            current->y += by.y;
            current->z += by.z;
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
        assert(s == s);
        assert(c == c);

        x = p.x, y = p.y, z = p.z;

        p.y = (c * y) - (s * z);
        p.z = (s * y) + (c * z);
    }

    if (by.y != 0)
    {
        s = SDL_sinf(by.y), c = SDL_cosf(by.y);
        assert(s == s);
        assert(c == c);

        x = p.x, y = p.y, z = p.z;

        p.x = (c * x) + (s * z);
        p.z = (s * -x) + (c * z);
    }

    if (by.z != 0)
    {
        s = SDL_sinf(by.z), c = SDL_cosf(by.z);
        assert(s == s);
        assert(c == c);

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