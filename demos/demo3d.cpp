#include "../jgame3D/points3d.hpp"
#include "../jgame3D/keys.hpp"

#include <vector>
using namespace std;

//////////////////////////////////////////////////

GameSpace *space;
Polygon3D *poly;
unsigned char r, g, b;

//////////////////////////////////////////////////

#define stepSize 1
void update(vector<Polygon3D *> &polys)
{

    if (space->key(27))
    {
        space->isRunning = false;
    }

    if (space->key(keys::leftArrow))
    {
        poly->basis.x -= stepSize;
    }
    else if (space->key(keys::rightArrow))
    {
        poly->basis.x += stepSize;
    }

    if (space->key(keys::upArrow))
    {
        poly->basis.y -= stepSize;
    }
    else if (space->key(keys::downArrow))
    {
        poly->basis.y += stepSize;
    }

    if (space->key(keys::w))
    {
        poly->basis.z += stepSize;
    }
    else if (space->key(keys::s))
    {
        poly->basis.z -= stepSize;
    }

    SDL_SetRenderDrawColor(space->rend, 0, 0, 0, 255);
    SDL_RenderClear(space->rend);

    SDL_SetRenderDrawColor(space->rend, 255, 255, 255, 255);

    poly->rotationX += .01;
    poly->rotationY += .01;
    poly->rotationZ += .01;

    return;
}

//////////////////////////////////////////////////

int main()
{
    Point3D points[] = {Point3D(-32, -32, -32),
                        Point3D(32, -32, -32),
                        Point3D(32, 32, -32),
                        Point3D(-32, 32, -32),
                        Point3D(-32, -32, 32),
                        Point3D(32, -32, 32),
                        Point3D(32, 32, 32),
                        Point3D(-32, 32, 32)};

    poly = new Polygon3D(points, 8);
    poly->basis = Point3D(128, 128, 128);

    r = g = b = 255;

    poly->rotationX = poly->rotationY = poly->rotationZ = 0;

    space = new GameSpace(512, 512, 8, update, SDL_WINDOW_OPENGL);

    space->horizon.x = 256;
    space->horizon.y = 480;
    space->horizon.z = 1028;

    space->addPolygon(poly);
    space->mainLoop();

    delete poly;

    return 0;
}
