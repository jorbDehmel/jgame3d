#include "resources.hpp"

namespace colors
{
    SDL_Color red()
    {
        return makeColor(255, 0, 0, 255);
    }

    SDL_Color green()
    {
        return makeColor(0, 255, 0, 255);
    }

    SDL_Color blue()
    {
        return makeColor(0, 0, 255, 255);
    }

    SDL_Color black()
    {
        return makeColor(0, 0, 0, 255);
    }
    
    SDL_Color grey()
    {
        return makeColor(128, 128, 128, 255);
    }
    
    SDL_Color white()
    {
        return makeColor(255, 255, 255, 255);
    }
};

void createCube(Model &obj, vector<SDL_Color> &colors)
{
    vector<Point3D> tbSquare = {
        Point3D(0, 0, 0),
        Point3D(64, 0, 0),
        Point3D(64, 64, 0),
        Point3D(0, 64, 0)};

    Polygon top;
    top.points = tbSquare;
    top.color = colors[0];
    move(top, Point3D(-32, -32, 32));

    Polygon bottom;
    bottom.points = tbSquare;
    bottom.color = colors[1];
    move(bottom, Point3D(-32, -32, -32));

    /////////////////////////////

    vector<Point3D> lrSquare = {
        Point3D(0, 0, 0),
        Point3D(0, 64, 0),
        Point3D(0, 64, 64),
        Point3D(0, 0, 64)};

    Polygon right;
    right.points = lrSquare;
    right.color = colors[2];
    move(right, Point3D(32, -32, -32));

    Polygon left;
    left.points = lrSquare;
    left.color = colors[3];
    move(left, Point3D(-32, -32, -32));

    ////////////////////

    vector<Point3D> fbSquare = {
        Point3D(0, 0, 0),
        Point3D(64, 0, 0),
        Point3D(64, 0, 64),
        Point3D(0, 0, 64)};

    Polygon front;
    front.points = fbSquare;
    front.color = colors[4];
    move(front, Point3D(-32, 32, -32));

    Polygon back;
    back.points = fbSquare;
    back.color = colors[5];
    move(back, Point3D(-32, -32, -32));

    obj.polygons.push_back(right);
    obj.polygons.push_back(left);

    obj.polygons.push_back(top);
    obj.polygons.push_back(bottom);

    obj.polygons.push_back(front);
    obj.polygons.push_back(back);

    move(obj, Point3D(64, 64, 256));

    return;
}