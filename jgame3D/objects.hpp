#ifndef OBJECTS_H
#define OBJECTS_H

#include "points3d.hpp"
#include "textures.hpp"

class Object
{
public:
    Object();
    void add(Polygon3D other);

    void render(SDL_Renderer *rend, Point3D &horizon);
    void renderCross(SDL_Renderer *rend, Point3D &horizon);

    void fill(SDL_Renderer *rend, vector<Uint32> &colors, Point3D &horizon);

    double rotationX, rotationY, rotationZ;
    Point3D basis, min, max;

    vector<Polygon3D> shapes;
};

/////////////////////////////////////////

Object move(const Object poly);
Object rotate(const Object poly);

/////////////////////////////////////////

class GameSpace
{
public:
    GameSpace(int height, int width, int rt, void (*updateFunc)(vector<Object *> &),
              SDL_WindowFlags windowFlag);
    ~GameSpace();

    void runFrame();
    void scanEvents();
    void kill();

    bool key(int k) const;

    void mainLoop();

    void addPolygon(Object *);
    void removePolygon(Object *);
    void removePolygons(bool (*checkingFunction)(const Object *));

    SDL_Renderer *rend;

    Point3D horizon;

    SDL_Window *wind;
    vector<Object *> polygons;

    set<Uint8> keys;
    int mouseX, mouseY, mouseState;

    void (*update)(vector<Object *> &);

    int refreshTime;
    bool isRunning;
    int passed;
    int prevTicks;
};

/////////////////////////////////////////

#endif
