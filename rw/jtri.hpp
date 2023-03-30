/*
Jordan "Jorb" Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2023 - present
GPLv3 held by author
*/

#ifndef JTRI_HPP
#define JTRI_HPP

#include <SDL2/SDL.h>
#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <cassert>
#include <queue>
using namespace std;

extern double dy;
extern double h;
extern double w;
extern double FOVScalar;
extern double renderMinX, renderMinY;
extern double renderMaxX, renderMaxY;

struct Point
{
    double x, y, z;
};

extern Point focus;

struct Point2D
{
    double x, y;
};

struct Rotation
{
    double x, y, z;
};

struct Triangle
{
    SDL_Color color;
    Point a, b, c;
};

struct Triangle2D
{
    SDL_Color color;
    Point2D a, b, c;
};

struct Object
{
    Rotation rot;
    Point offset;
    vector<Triangle> triangles;
};

class Camera
{
public:
    Camera();
    ~Camera();

    void clear();
    void update();
    void present();

    vector<Object> objects;
    Rotation cameraRot{0, 0, 0};
    Point cameraPos{0, 0, 0};

    SDL_Renderer *rend;
    SDL_Window *wind;
};

Point rotate(const Point &What, const Point &About, const Rotation &By);
Point2D rotate(const Point2D &What, const Point2D &About, const double &By);
Triangle rotate(const Triangle &What, const Point &About, const Rotation &By);
Triangle2D rotate(const Triangle2D &What, const Point2D &About, const double &By);

Object rotate(const Object &What, const Point &About, const Rotation &By);

Point move(const Point &What, const Point &By);
Point2D move(const Point2D &What, const Point2D &By);
Triangle move(const Triangle &What, const Point &By);
Triangle2D move(const Triangle2D &What, const Point2D &By);

Object move(const Object &What, const Point &By);

Point2D project(const Point &What);
Triangle2D project(const Triangle &What);

void render(const Triangle2D &What, SDL_Renderer *With);

#endif
