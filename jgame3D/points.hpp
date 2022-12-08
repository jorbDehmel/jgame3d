#ifndef POINTS_H
#define POINTS_H

#include <SDL2/SDL.h>

// #include "keys.hpp"

#include <vector>
#include <cassert>
#include <iostream>
#include <cmath>
#include <set>

using namespace std;

/////////////////////////////////////////

class BasicPoint
{
public:
    BasicPoint() : x(0), y(0){};
    BasicPoint(double xIn, double yIn) : x(xIn), y(yIn){};
    double x, y;
};

ostream &operator<<(ostream &stream, const BasicPoint &point);

/////////////////////////////////////////

struct Pixel
{
    Pixel(unsigned char R, unsigned char G, unsigned char B, unsigned char A) : r(R), g(G), b(B), a(A) {}
    Pixel() : r(0), g(0), b(0), a(0) {}

    unsigned char r, g, b, a;
};

struct Rotation
{
    Rotation(double X, double Y, double Z) : x(X), y(Y), z(Z) {}
    Rotation() : x(0), y(0), z(0) {}
    double x, y, z;
};

/////////////////////////////////////////

class Polygon2D
{
public:
    Polygon2D() : rotation(0)
    {
        basis = min = max = BasicPoint(0, 0);
        points.clear();
    }
    Polygon2D(BasicPoint pointsIn[], int num);
    SDL_FPoint *SDLify();

    void operator+=(Polygon2D &other);

    int render(SDL_Renderer *renderer);
    void renderCross(SDL_Renderer *renderer);
    void checkMinMax();

    double rotation;
    BasicPoint basis, min, max;
    vector<BasicPoint> points;
};

/////////////////////////////////////////

void move(Polygon2D &poly, BasicPoint by);
void rotate(Polygon2D &poly, double degree, BasicPoint about);
void rotate(Polygon2D &poly, double degree);

/////////////////////////////////////////

class RenderWindow
{
public:
    RenderWindow(int h, int w, int rt, void (*update)(SDL_Renderer *),
                 SDL_WindowFlags windowFlags);
    ~RenderWindow();

    void scanEvents();
    void runFrame();
    void mainLoop();
    void kill();

    bool key(int k) const;

    set<Uint8> keys;
    int mouseX, mouseY, mouseState;

    SDL_Window *wind;
    SDL_Renderer *rend;
    void (*updateFunc)(SDL_Renderer *);

    int refreshTime;
    bool isRunning;

    int passed;
    int prevTicks;
};

/////////////////////////////////////////

#endif
