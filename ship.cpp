#include "points.hpp"
#include "keys.hpp"

using namespace std;

//////////////////////////////////////////////////

RenderWindow *wind;
Polygon2D *poly;

//////////////////////////////////////////////////

double rotVel, xVel, yVel;
void update(SDL_Renderer *rend)
{
    if (wind->key(27))
    {
        wind->isRunning = false;
    }

    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
    SDL_RenderClear(rend);

    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    SDL_RenderDrawLinesF(rend, *poly);

    if (wind->key(keys::space))
    {
        xVel += cos(poly->rotation);
        yVel += sin(poly->rotation);
    }

    if (wind->key(keys::leftArrow))
    {
        if (rotVel > -1)
            rotVel -= 0.01;
    }
    else if (wind->key(keys::rightArrow))
    {
        if (rotVel < 1)
            rotVel += 0.01;
    }
    else if (rotVel < 0)
    {
        rotVel += .001;
    }
    else if (rotVel > 0)
    {
        rotVel -= .001;
    }

    poly->basis.x += xVel;
    poly->basis.y += yVel;

    if (poly->basis.x > 512)
    {
        poly->basis.x = -200;
    }
    else if (poly->basis.x < -200)
    {
        poly->basis.x = 512;
    }
    else if (poly->basis.y > 712)
    {
        poly->basis.y = -200;
    }
    else if (poly->basis.y < -200)
    {
        poly->basis.y = 712;
    }

    poly->rotation += rotVel;

    return;
}

//////////////////////////////////////////////////

int main()
{
    rotVel = 0;
    xVel = yVel = 0;

    BasicPoint points[4] = {
        BasicPoint(0, -50),
        BasicPoint(200, 0),
        BasicPoint(0, 50),
        BasicPoint(50, 0)};

    poly = new Polygon2D(points, 4);
    poly->basis = BasicPoint(256, 256);

    wind = new RenderWindow(512, 512, 10, update, SDL_WINDOW_OPENGL);
    wind->mainLoop();

    return 0;
}