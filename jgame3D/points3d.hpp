#ifndef POINTS3D_H
#define POINTS3D_H

#include "points.hpp"

/////////////////////////////////////////

class Point3D
{
public:
    Point3D() {}
    Point3D(double xIn, double yIn, double zIn) : x(xIn), y(yIn), z(zIn) {}
    double x, y, z;
};

/////////////////////////////////////////

class Polygon3D
{
public:
    Polygon3D(Point3D pointsIn[], int num);
    SDL_FPoint *SDLify(Point3D &horizon) const;

    void operator+=(Polygon3D &other);

    double rotationX, rotationY, rotationZ;
    Point3D basis;
    vector<Point3D> points;
};

/////////////////////////////////////////

int SDL_RenderDrawLinesF(SDL_Renderer *renderer, const Polygon3D polygon, Point3D &horizon);
void crossDrawLines(SDL_Renderer *renderer, const Polygon3D &polygon, Point3D &horizon);
Polygon3D move(const Polygon3D poly);
Polygon3D rotate(const Polygon3D poly);
void rotatePoint(Point3D &p, double dx, double dy, double dz);

/////////////////////////////////////////

class GameSpace
{
public:
    GameSpace(int height, int width, int rt, void (*updateFunc)(vector<Polygon3D *> &),
              SDL_WindowFlags windowFlag);
    ~GameSpace();

    void runFrame();
    void scanEvents();
    void kill();

    bool key(int k) const;

    void mainLoop();

    void addPolygon(Polygon3D *);
    void removePolygon(Polygon3D *);
    void removePolygons(bool (*checkingFunction)(const Polygon3D *));

    SDL_Renderer *rend;

    Point3D horizon;

    SDL_Window *wind;
    vector<Polygon3D *> polygons;

    set<Uint8> keys;
    int mouseX, mouseY, mouseState;

    void (*update)(vector<Polygon3D *> &);

    int refreshTime;
    bool isRunning;
    int passed;
    int prevTicks;
};

/////////////////////////////////////////

#endif
