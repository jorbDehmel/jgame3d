#include "../jgame3D/points3d.hpp"
#include "../jgame3D/keys.hpp"

#include <vector>
using namespace std;

//////////////////////////////////////////////////

RenderWindow *wind;
Polygon3D *poly;

//////////////////////////////////////////////////

#define stepSize 1
void update(SDL_Renderer *rend)
{
    SDL_Delay(10);

    if (wind->key(27))
    {
        wind->isRunning = false;
    }

    if (wind->key(keys::leftArrow))
    {
        poly->basis.x -= stepSize;
    }

    if (wind->key(keys::rightArrow))
    {
        poly->basis.x += stepSize;
    }

    if (wind->key(keys::upArrow))
    {
        poly->basis.y -= stepSize;
    }

    if (wind->key(keys::downArrow))
    {
        poly->basis.y += stepSize;
    }

    if (wind->key(keys::w))
    {
        poly->basis.z += stepSize;
    }

    if (wind->key(keys::s))
    {
        poly->basis.z -= stepSize;
    }

    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
    SDL_RenderClear(rend);

    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);

    crossDrawLines(rend, *poly);

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

    poly->rotationX = .5;
    poly->rotationY = poly->rotationZ = 0;

    wind = new RenderWindow(512, 512, 0, update, SDL_WINDOW_OPENGL);
    wind->mainLoop();

    delete wind;
    delete poly;

    return 0;
}
