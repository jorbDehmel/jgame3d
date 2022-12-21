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

void fillPolygon(SDL_Renderer *rend, Polygon3D &poly, Pixel color)
{

    Polygon3D p = rotate(poly);
    p = move(p);

    // Convert to Polygon2D
    Polygon2D toFill = p.project();
    fillPolygon(rend, toFill, color);

    return;
}

void renderSlice(SDL_Renderer *rend, Polygon3D &poly, Pixel color)
{
    if (poly.basis.z > globalHorizon.z || poly.basis.z < 0)
    {
        return;
    }

    Polygon3D p = rotate(poly);
    p = move(p);

    p.checkMinMax();
    for (double z = p.max.z; z > p.min.z; z -= 1)
    {
        vector<BasicPoint> points;

        for (int i = 0; i < p.points.size(); i++)
        {
            Point3D A = p.points[i];
            Point3D B = p.points[(i + 1) % (p.points.size())];

            double X1, X2, Y1, Y2, Z1, Z2;
            X1 = A.x, X2 = B.x;
            Y1 = A.y, Y2 = B.y;
            Z1 = A.z, Z2 = B.z;

            BasicPoint out;

            // Continue if out of range
            if (Z1 < z && Z2 < z)
                continue;
            else if (Z1 > z && Z2 > z)
                continue;
            else if (Z2 == Z1) // asymptote check
                continue;

            // Compute coords for out here
            out.x = z * ((X2 - X1) / (Z2 - Z1)) - Z1 * ((X2 - X1) / (Z2 - Z1)) + X1;
            out.y = z * ((Y2 - Y1) / (Z2 - Z1)) - Z1 * ((Y2 - Y1) / (Z2 - Z1)) + Y1;

            // Project onto plane via z-coord
            out.x -= globalHorizon.x;
            out.y -= globalHorizon.y;

            out.x *= (FOV_SCALAR / z);
            out.y *= (FOV_SCALAR / z);

            out.x += globalHorizon.x;
            out.y += globalHorizon.y;

            // Add to list of points
            points.push_back(out);
        }

        if (points.size() == 0)
            continue;

        BasicPoint bpoints[points.size()];
        for (int j = 0; j < points.size(); j++)
            bpoints[j] = points[j];

        Polygon2D subRect(bpoints, points.size());
        fillPolygon(rend, subRect, color);
    }

    return;
}

void renderSlice(SDL_Renderer *rend, Object &obj, vector<Pixel> colors)
{
    vector<Polygon3D> rawPolys;
    for (int i = 0; i < obj.shapes.size(); i++)
    {
        rawPolys.push_back(move(rotate(obj.shapes[i])));
    }

    // Prepare min and max
    vector<Polygon3D> polys;
    double minZ = rawPolys[0].min.z, maxZ = rawPolys[0].max.z;

    // Prepare real positions of polygons
    for (auto poly : rawPolys)
    {
        Polygon3D p = rotate(poly);
        p = move(p);
        p.checkMinMax();

        polys.push_back(p);

        if (p.min.z < minZ)
            minZ = p.min.z;
        else if (p.max.z > maxZ)
            maxZ = p.max.z;
    }

    // Iterate over z
    for (double z = maxZ; z > minZ; z -= 1)
    {
        // Iterate over
        int ind = 0;
        for (auto p : polys)
        {
            vector<BasicPoint> points;

            for (int i = 0; i < p.points.size(); i++)
            {
                Point3D A = p.points[i];
                Point3D B = p.points[(i + 1) % (p.points.size())];

                double X1, X2, Y1, Y2, Z1, Z2;
                X1 = A.x, X2 = B.x;
                Y1 = A.y, Y2 = B.y;
                Z1 = A.z, Z2 = B.z;

                BasicPoint out;

                // Continue if out of range
                if (Z1 < z && Z2 < z)
                    continue;
                else if (Z1 > z && Z2 > z)
                    continue;
                else if (Z2 == Z1) // asymptote check
                    continue;

                // Compute coords for out here
                out.x = z * ((X2 - X1) / (Z2 - Z1)) - Z1 * ((X2 - X1) / (Z2 - Z1)) + X1;
                out.y = z * ((Y2 - Y1) / (Z2 - Z1)) - Z1 * ((Y2 - Y1) / (Z2 - Z1)) + Y1;

                // Project onto plane via z-coord
                out.x -= globalHorizon.x;
                out.y -= globalHorizon.y;

                out.x *= (FOV_SCALAR / z);
                out.y *= (FOV_SCALAR / z);

                out.x += globalHorizon.x;
                out.y += globalHorizon.y;

                // Add to list of points
                points.push_back(out);
            }

            if (points.size() == 0)
                continue;

            BasicPoint bpoints[points.size()];
            for (int j = 0; j < points.size(); j++)
                bpoints[j] = points[j];

            Polygon2D subRect(bpoints, points.size());
            fillPolygon(rend, subRect, colors[ind]);

            ind++;
        }
    }

    return;
}
