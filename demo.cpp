#include "points.hpp"

using namespace std;

//////////////////////////////////////////////////

RenderWindow *wind;
Polygon2D *poly;

//////////////////////////////////////////////////

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

    rotate(*poly, .01, BasicPoint(256, 256));
    return;
}

//////////////////////////////////////////////////

int main()
{
    BasicPoint points[4] = {BasicPoint(256, 200), BasicPoint(200, 200), BasicPoint(230, 270), BasicPoint(270, 270)};
    poly = new Polygon2D(points, 4);

    wind = new RenderWindow(512, 512, 10, update, SDL_WINDOW_OPENGL);
    wind->mainLoop();

    return 0;
}