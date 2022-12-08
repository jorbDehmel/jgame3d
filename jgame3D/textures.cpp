#include "textures.hpp"

int X_RENDER_THRESH = 1000, Y_RENDER_THRESH = 1000;

void fillPolygon(SDL_Renderer *rend, Polygon2D &poly, Pixel color)
{
    Polygon2D p = poly;

    rotate(p, p.rotation);
    move(p, p.basis);
    p.checkMinMax();

    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);

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
                continue;
            else if (Y1 > y && Y2 > y)
                continue;
            else if (Y1 == Y2)
                continue;
            else if (Y1 - globalHorizon.y > Y_RENDER_THRESH || Y1 - globalHorizon.y < -Y_RENDER_THRESH)
                continue;
            else if (Y2 - globalHorizon.y > Y_RENDER_THRESH || Y2 - globalHorizon.y < -Y_RENDER_THRESH)
                continue;
            else if (X1 - globalHorizon.x > X_RENDER_THRESH || X1 - globalHorizon.x < -X_RENDER_THRESH)
                continue;
            else if (X2 - globalHorizon.x > X_RENDER_THRESH || X2 - globalHorizon.x < -X_RENDER_THRESH)
                continue;

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

void fillPolygon(SDL_Renderer *rend, Polygon3D &poly, Pixel color)
{

    Polygon3D p = rotate(poly);
    p = move(p);

    // Convert to Polygon2D
    Polygon2D toFill = p.project();
    fillPolygon(rend, toFill, color);

    return;
}
