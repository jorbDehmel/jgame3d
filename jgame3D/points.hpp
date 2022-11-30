#ifndef POINTS_H
#define POINTS_H

#include <SDL2/SDL.h>

//#include "keys.hpp"

#include <vector>
#include <cassert>
#include <iostream>
#include <cmath>
#include <set>

using namespace std;

/////////////////////////////////////////

double modulo(const double &a, const double &b);

/////////////////////////////////////////

class BasicPoint
{
public:
    BasicPoint() : x(0), y(0){};
    BasicPoint(double xIn, double yIn) : x(xIn), y(yIn){};
    double x, y;
};

/////////////////////////////////////////

class Polygon2D
{
public:
    Polygon2D(BasicPoint pointsIn[], int num);
    SDL_FPoint *SDLify();

    void operator+=(Polygon2D &other);

    double rotation;
    BasicPoint basis;
    vector<BasicPoint> points;
};

/////////////////////////////////////////

int SDL_RenderDrawLinesF(SDL_Renderer *renderer, const Polygon2D &polygon);
void crossDrawLines(SDL_Renderer *renderer, const Polygon2D &polygon);
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
