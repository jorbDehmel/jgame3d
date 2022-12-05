#include "textures.hpp"
#include <algorithm>

void fillPolygon(SDL_Renderer *rend, Polygon2D &poly, const unsigned int color)
{
    Polygon2D p = poly;

    rotate(p, p.rotation);
    move(p, p.basis);
    p.SDLify();

    SDL_SetRenderDrawColor(rend, ((unsigned char *)&color)[0], ((unsigned char *)&color)[1], ((unsigned char *)&color)[2], ((unsigned char *)&color)[3]);

    double X1, X2, Y1, Y2;
    vector<double> xValues;

    for (int y = p.min.y; y < p.max.y; y++)
    {
        xValues.clear();
        for (int i = 0; i < p.points.size(); i++)
        {
            X1 = p.points[i].x;
            Y1 = p.points[i].y;
            X2 = p.points[(i + 1) % (p.points.size())].x;
            Y2 = p.points[(i + 1) % (p.points.size())].y;

            if (Y1 < y && Y2 < y)
            {
                continue;
            }
            else if (Y1 > y && Y2 > y)
            {
                continue;
            }
            else if (Y1 == Y2 || X1 == X2)
            {
                continue;
            }

            xValues.push_back(y * ((X2 - X1) / (Y2 - Y1)) - Y1 * ((X2 - X1) / (Y2 - Y1)) + X1);
        }

        if (xValues.size() <= 1)
            continue;

        sort(xValues.begin(), xValues.end());

        // Draw line segments
        for (int i = 0; i < xValues.size(); i += 2)
        {
            // cout << "Drawing line between " << xValues[i] << " and " << xValues[(i + 1) % (xValues.size() - 1)] << " along y = " << y << '\n';
            SDL_RenderDrawLineF(rend, xValues[i], y, xValues[(i + 1) % (xValues.size())], y);
        }
    }

    return;
}

void fillPolygon(SDL_Renderer *rend, Polygon3D &poly, const unsigned int color)
{
    Polygon3D p = rotate(poly);
    p = move(p);

    // Convert to Polygon2D
    Polygon2D toFill = p.project();
    fillPolygon(rend, toFill, color);

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
