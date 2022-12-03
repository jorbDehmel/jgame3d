#include "../jgame3D/jgame3D.hpp"
#include <iostream>
using namespace std;

Polygon2D *poly;
RenderWindow *renderer;

void update(SDL_Renderer *r)
{
    if (renderer->key(keys::esc))
        renderer->isRunning = false;

    SDL_SetRenderDrawColor(renderer->rend, 0, 0, 0, 255);
    SDL_RenderClear(renderer->rend);

    SDL_SetRenderDrawColor(renderer->rend, 255, 255, 255, 255);
    SDL_RenderDrawLinesF(renderer->rend, *poly);

    fillPolygon(r, *poly, 0b1111'1111'1111'1111'1111'1111'1111'1111);

    return;
}

int main()
{
    BasicPoint points[4] = {BasicPoint(128, 128),
                            BasicPoint(256, 128),
                            BasicPoint(256, 256),
                            BasicPoint(128, 256)};
    poly = new Polygon2D(points, 4);

    renderer = new RenderWindow(512, 512, 0, update, SDL_WINDOW_OPENGL);
    renderer->mainLoop();

    delete poly;
    delete renderer;

    return 0;
}