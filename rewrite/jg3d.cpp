#include "jg3d.hpp"

//////////////////////////////

int FOV_SCALAR = 500;
Point3D horizon(100, 100, 100);
double dz = .5;

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

//////////////////////////////

Renderer::Renderer(SDL_Renderer *&Rend, SDL_Window *&Wind)
{
    rend = Rend;
    wind = Wind;
}

void Renderer::render()
{
    // Prepare min and max
    vector<Polygon> polys;
    double minZ = models[0]->polygons[0].points[0].z, maxZ = minZ;

    // Prepare real positions of polygons
    for (Model *m : models)
    {
        for (Polygon p : m->polygons)
        {
            polys.push_back(p);

            for (auto point : p.points)
            {
                if (point.z < minZ)
                    minZ = point.z;
                else if (point.z > maxZ)
                    maxZ = point.z;
            }
        }
    }

    // Iterate over z
    for (double z = maxZ; z > minZ; z -= dz)
    {
        // Iterate over
        int ind = 0;
        for (auto p : polys)
        {
            vector<SDL_FPoint> points;

            for (int i = 0; i < p.points.size(); i++)
            {
                Point3D A = p.points[i];
                Point3D B = p.points[(i + 1) % (p.points.size())];

                double X1, X2, Y1, Y2, Z1, Z2;
                X1 = A.x, X2 = B.x;
                Y1 = A.y, Y2 = B.y;
                Z1 = A.z, Z2 = B.z;

                SDL_FPoint out;

                // Continue if out of range
                if (Z1 < z && Z2 < z)
                    continue;
                else if (Z1 > z && Z2 > z)
                    continue;
                else if (Z2 == Z1) // asymptote check
                    continue;

                // Compute coords for out
                out.x = z * ((X2 - X1) / (Z2 - Z1)) - Z1 * ((X2 - X1) / (Z2 - Z1)) + X1;
                out.y = z * ((Y2 - Y1) / (Z2 - Z1)) - Z1 * ((Y2 - Y1) / (Z2 - Z1)) + Y1;

                // Project onto plane via z-coord
                out.x -= horizon.x;
                out.y -= horizon.y;

                out.x *= (FOV_SCALAR / z);
                out.y *= (FOV_SCALAR / z);

                out.x += horizon.x;
                out.y += horizon.y;

                // Add to list of points
                // cout << out.x << '\t' << out.y << '\n';
                points.push_back(out);
            }

            if (points.size() == 0)
                continue;

            points.push_back(points[0]);

            SDL_FPoint rawPoints[points.size()];
            for (int i = 0; i < points.size(); i++)
                rawPoints[i] = points[i];

            SDL_SetRenderDrawColor(rend, p.color.r, p.color.g, p.color.b, p.color.a);
            SDL_RenderDrawLinesF(rend, rawPoints, points.size());

            ind++;
        }
    }

    return;
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
    Point3D *current;
    for (int shapeNum = 0; shapeNum < m.polygons.size(); shapeNum++)
    {
        for (int pointNum = 0; pointNum < m.polygons[shapeNum].points.size(); pointNum++)
        {
            current = &m.polygons[shapeNum].points[pointNum];

            current->x -= about.x;
            current->y -= about.y;
            current->z -= about.z;

            rotate(*current, by);

            current->x += about.x;
            current->y += about.y;
            current->z += about.z;
        }
    }
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

    for (double y = yMin; y < yMax; y++)
    {
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
            else if (Y1 == Y2)
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