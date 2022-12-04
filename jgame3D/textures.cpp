#include "textures.hpp"
#include <algorithm>

Sprite3D::Sprite3D(Object &o, vector<SDL_Surface *> &t)
{
    obj = o;
    textures.clear();
    for (int i = 0; i < t.size(); i++)
    {
        textures.push_back(t[i]);
    }
}

void fillPolygon(SDL_Renderer *rend, Polygon2D &poly, const unsigned int color)
{
    Polygon2D p = poly;

    rotate(p, p.rotation, p.basis);
    move(p, p.basis);

    SDL_SetRenderDrawColor(rend, ((unsigned char *)&color)[0], ((unsigned char *)&color)[1], ((unsigned char *)&color)[2], ((unsigned char *)&color)[3]);

    double X1, X2, Y1, Y2;

    vector<double> xValues;

    p.SDLify();
    for (int y = p.min.y; y < p.max.y; y++)
    {
        xValues.clear();
        for (int i = 0; i < p.points.size(); i++)
        {
            // if (p.points[i].y < y && p.points[(i + 1) % (p.points.size() - 1)].y < y)
            //     continue;
            // else if (p.points[i].y > y && p.points[(i + 1) % (p.points.size() - 1)].y > y)
            //     continue;

            X1 = p.points[i].x;
            Y1 = p.points[i].y;
            X2 = p.points[(i + 1) % (p.points.size() - 1)].x;
            Y2 = p.points[(i + 1) % (p.points.size() - 1)].y;

            xValues.push_back(y * ((X2 - X1) / (Y2 - Y1)) - (Y1 * (X2 - X1) / (Y2 - Y1)) + X1);
        }

        sort(xValues.begin(), xValues.end());

        // Draw line segments
        for (int i = 0; i < xValues.size(); i += 2)
        {
            cout << "Drawing line between " << xValues[i] << " and " << xValues[(i + 1) % (xValues.size() - 1)] << " along y = " << y << '\n';
            SDL_RenderDrawLineF(rend, xValues[i], y, xValues[(i + 1) % (xValues.size() - 1)], y);
        }
    }

    return;
}

void fillPolygon(SDL_Renderer *rend, Polygon3D &p, const unsigned int color, Point3D horizon)
{
    // Convert to Polygon2D
    SDL_FPoint *SDLpoints = p.SDLify(horizon);
    BasicPoint *basicPoints = new BasicPoint[p.points.size()];

    for (int i = 0; i < p.points.size(); i++)
    {
        basicPoints[i].x = SDLpoints[i].x;
        basicPoints[i].y = SDLpoints[i].y;
        cout << SDLpoints[i].x << '\t' << SDLpoints[i].y << '\n';
        cout << basicPoints[i] << '\n';
    }

    Polygon2D polygon(basicPoints, (int)p.points.size());
    polygon.SDLify();

    fillPolygon(rend, polygon, color);

    return;
}

void mapSurface(SDL_Renderer *rend, const SDL_Surface *surface, const Polygon3D &p)
{
    return;
}

void textureObject(SDL_Renderer *rend, const Object &obj)
{
    return;
}
