#include "../jgame3D/points3d.hpp"
#include "../jgame3D/keys.hpp"
#include "../jgame3D/objects.hpp"
#include "../jgame3D/textures.hpp"

#include <vector>
using namespace std;

//////////////////////////////////////////////////

GameSpace *space;
unsigned char r, g, b;
vector<Uint32> colors = {
    0xff'00'00'ff,
    0x00'ff'00'ff,
    0x00'00'ff'ff,
    0xff'ff'00'ff,
    0xff'00'ff'ff,
    0x00'ff'ff'ff};

//////////////////////////////////////////////////

#define stepSize 1
void update(vector<Object *> &polygons)
{
    Object *poly = polygons[0];

    if (space->key(27))
        space->isRunning = false;

    if (space->key(keys::leftArrow))
        poly->basis.x -= stepSize;
    else if (space->key(keys::rightArrow))
        poly->basis.x += stepSize;

    if (space->key(keys::upArrow))
        poly->basis.y -= stepSize;
    else if (space->key(keys::downArrow))
        poly->basis.y += stepSize;

    if (space->key(keys::w))
        poly->basis.z += stepSize;
    else if (space->key(keys::s))
        poly->basis.z -= stepSize;

    SDL_SetRenderDrawColor(space->rend, 0, 0, 0, 255);
    SDL_RenderClear(space->rend);

    poly->fill(space->rend, colors, space->horizon);

    poly->rotationX += .001;
    poly->rotationY += .001;
    poly->rotationZ += .001;

    return;
}

//////////////////////////////////////////////////

void createCube(Object &obj)
{
    Point3D tbSquare[4] = {
        Point3D(0, 64, 0),
        Point3D(64, 64, 0),
        Point3D(64, 0, 0),
        Point3D(0, 0, 0)};

    Polygon3D top(tbSquare, 4);
    top.basis = Point3D(-32, -32, 32);

    Polygon3D bottom(tbSquare, 4);
    bottom.basis = Point3D(-32, -32, -32);

    /////////////////////////////

    Point3D lrSquare[4] = {
        Point3D(0, 0, 0),
        Point3D(0, 64, 0),
        Point3D(0, 64, 64),
        Point3D(0, 0, 64)};

    Polygon3D right(lrSquare, 4);
    right.basis = Point3D(32, -32, -32);

    Polygon3D left(lrSquare, 4);
    left.basis = Point3D(-32, -32, -32);

    ////////////////////

    Point3D fbSquare[4] = {
        Point3D(0, 0, 0),
        Point3D(64, 0, 0),
        Point3D(64, 0, 64),
        Point3D(0, 0, 64)};

    Polygon3D front(fbSquare, 4);
    front.basis = Point3D(-32, 32, -32);

    Polygon3D back(fbSquare, 4);
    back.basis = Point3D(-32, -32, -32);

    obj.add(right);
    obj.add(left);
    obj.add(top);
    obj.add(bottom);
    obj.add(front);
    obj.add(back);

    return;
}

//////////////////////////////////////////////////

int main()
{
    r = g = b = 255;

    Object poly;
    poly.basis = Point3D(256, 256, 256);
    createCube(poly);

    space = new GameSpace(512, 512, 0, update, SDL_WINDOW_OPENGL);

    space->horizon.x = 256;
    space->horizon.y = 256;
    space->horizon.z = 512;

    space->addPolygon(&poly);

    space->mainLoop();

    return 0;
}
