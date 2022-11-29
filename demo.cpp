#include "points.hpp"
#include "keys.hpp"

using namespace std;

//////////////////////////////////////////////////

RenderWindow *wind;
Polygon2D *poly;

//////////////////////////////////////////////////

double rotVel;
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
    else if (rotVel < -0.01)
    {
        rotVel += .001;
    }
    else if (rotVel > 0.01)
    {
        rotVel -= .001;
    }

    rotate(*poly, rotVel);

    return;
}

//////////////////////////////////////////////////

int main()
{
    rotVel = 0;

    BasicPoint points[4] = {BasicPoint(256, 200), BasicPoint(200, 200), BasicPoint(230, 270), BasicPoint(270, 270)};
    poly = new Polygon2D(points, 4);

    wind = new RenderWindow(512, 512, 10, update, SDL_WINDOW_OPENGL);
    wind->mainLoop();

    return 0;
}