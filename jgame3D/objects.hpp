#ifndef OBJECTS_H
#define OBJECTS_H

#include "points3d.hpp"
#include "textures.hpp"

class Object
{
public:
    Object();
    void add(Polygon3D other);

    void render(SDL_Renderer *rend);
    void renderCross(SDL_Renderer *rend);

    void fill(SDL_Renderer *rend, vector<Pixel> &colors);
    void checkMinMax();

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
              double scaleX = 1, double scaleY = 1, SDL_WindowFlags windowFlag = SDL_WINDOW_OPENGL);
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
