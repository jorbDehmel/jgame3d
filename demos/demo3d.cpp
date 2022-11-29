#include "../points3d.hpp"
#include "../keys.hpp"

//////////////////////////////////////////////////

RenderWindow *wind;
Polygon3D *poly;

//////////////////////////////////////////////////

void update(SDL_Renderer *rend)
{
    SDL_Delay(10);

    if (wind->key(27))
    {
        wind->isRunning = false;
    }

    if (wind->key(keys::leftArrow))
    {
        poly->basis.x -= 5;
    }

    if (wind->key(keys::rightArrow))
    {
        poly->basis.x += 5;
    }

    if (wind->key(keys::upArrow))
    {
        poly->basis.y -= 5;
    }

    if (wind->key(keys::downArrow))
    {
        poly->basis.y += 5;
    }

    if (wind->key(keys::w))
    {
        poly->basis.z += 5;
    }

    if (wind->key(keys::s))
    {
        poly->basis.z -= 5;
    }

    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
    SDL_RenderClear(rend);

    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
    SDL_RenderDrawLinesF(rend, *poly);

    poly->rotationX += .01;
    // poly->rotationY += .1;
    // poly->rotationZ += .1;

    return;
}

//////////////////////////////////////////////////

int main()
{
    Point3D points[] = {Point3D(64, 64, 0),
                        Point3D(128, 64, 0),
                        Point3D(128, 128, 0),
                        Point3D(64, 128, 0),
                        Point3D(64, 64, 64),
                        Point3D(128, 64, 64),
                        Point3D(128, 128, 64),
                        Point3D(64, 128, 64)};
    poly = new Polygon3D(points, 8);
    poly->basis = Point3D(-100, 0, 0);

    poly->rotationX = poly->rotationY = poly->rotationZ = 0;

    wind = new RenderWindow(512, 512, 0, update, SDL_WINDOW_OPENGL);
    wind->mainLoop();

    delete wind;
    delete poly;

    return 0;
}
