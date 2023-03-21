/*
Jordan "Jorb" Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2022 - present
GPLv3 held by author
*/

#include "../resources.hpp"

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

void createCube(Model &obj, vector<SDL_Color> &colors, double sideLength)
{
    double moveBy = sideLength / 2;

    vector<Point3D> tbSquare = {
        Point3D(0, 0, 0),
        Point3D(sideLength, 0, 0),
        Point3D(sideLength, sideLength, 0),
        Point3D(0, sideLength, 0)};

    Polygon top;
    top.points = tbSquare;
    top.color = colors[0];
    move(top, Point3D(-moveBy, -moveBy, moveBy));

    Polygon bottom;
    bottom.points = tbSquare;
    bottom.color = colors[1];
    move(bottom, Point3D(-moveBy, -moveBy, -moveBy));

    /////////////////////////////

    vector<Point3D> lrSquare = {
        Point3D(0, 0, 0),
        Point3D(0, sideLength, 0),
        Point3D(0, sideLength, sideLength),
        Point3D(0, 0, sideLength)};

    Polygon right;
    right.points = lrSquare;
    right.color = colors[2];
    move(right, Point3D(moveBy, -moveBy, -moveBy));

    Polygon left;
    left.points = lrSquare;
    left.color = colors[3];
    move(left, Point3D(-moveBy, -moveBy, -moveBy));

    ////////////////////

    vector<Point3D> fbSquare = {
        Point3D(0, 0, 0),
        Point3D(sideLength, 0, 0),
        Point3D(sideLength, 0, sideLength),
        Point3D(0, 0, sideLength)};

    Polygon front;
    front.points = fbSquare;
    front.color = colors[4];
    move(front, Point3D(-moveBy, moveBy, -moveBy));

    Polygon back;
    back.points = fbSquare;
    back.color = colors[5];
    move(back, Point3D(-moveBy, -moveBy, -moveBy));

    obj.polygons.push_back(right);
    obj.polygons.push_back(left);

    obj.polygons.push_back(top);
    obj.polygons.push_back(bottom);

    obj.polygons.push_back(front);
    obj.polygons.push_back(back);

    return;
}

void createCube(Model &obj, SDL_Color &color, double sideLength)
{
    double moveBy = sideLength / 2;

    vector<Point3D> tbSquare = {
        Point3D(0, 0, 0),
        Point3D(sideLength, 0, 0),
        Point3D(sideLength, sideLength, 0),
        Point3D(0, sideLength, 0)};

    Polygon top;
    top.points = tbSquare;
    top.color = color;
    move(top, Point3D(-moveBy, -moveBy, moveBy));

    Polygon bottom;
    bottom.points = tbSquare;
    bottom.color = color;
    move(bottom, Point3D(-moveBy, -moveBy, -moveBy));

    /////////////////////////////

    vector<Point3D> lrSquare = {
        Point3D(0, 0, 0),
        Point3D(0, sideLength, 0),
        Point3D(0, sideLength, sideLength),
        Point3D(0, 0, sideLength)};

    Polygon right;
    right.points = lrSquare;
    right.color = color;
    move(right, Point3D(moveBy, -moveBy, -moveBy));

    Polygon left;
    left.points = lrSquare;
    left.color = color;
    move(left, Point3D(-moveBy, -moveBy, -moveBy));

    ////////////////////

    vector<Point3D> fbSquare = {
        Point3D(0, 0, 0),
        Point3D(sideLength, 0, 0),
        Point3D(sideLength, 0, sideLength),
        Point3D(0, 0, sideLength)};

    Polygon front;
    front.points = fbSquare;
    front.color = color;
    move(front, Point3D(-moveBy, moveBy, -moveBy));

    Polygon back;
    back.points = fbSquare;
    back.color = color;
    move(back, Point3D(-moveBy, -moveBy, -moveBy));

    obj.polygons.push_back(right);
    obj.polygons.push_back(left);

    obj.polygons.push_back(top);
    obj.polygons.push_back(bottom);

    obj.polygons.push_back(front);
    obj.polygons.push_back(back);

    return;
}

void createSquare(Model &obj, SDL_Color color, double sideLength)
{
    vector<Point3D> square = {
        Point3D(0, 0, 0),
        Point3D(sideLength, 0, 0),
        Point3D(sideLength, sideLength, 0),
        Point3D(0, sideLength, 0)};

    Polygon squarePolygon;
    squarePolygon.color = color;
    squarePolygon.points = square;

    obj.polygons.push_back(squarePolygon);

    return;
}