#include "../jgame3D/jgame3D.hpp"
#include <iostream>
using namespace std;

Polygon2D *poly;
RenderWindow *renderer;

void update(SDL_Renderer *r)
{
    if (renderer->key(keys::esc))
        renderer->isRunning = false;

    if (renderer->key(keys::upArrow) && poly->basis.y > 0)
        poly->basis.y--;
    else if (renderer->key(keys::downArrow) && poly->basis.y + 128 < 512)
        poly->basis.y++;
    if (renderer->key(keys::leftArrow) && poly->basis.x > 0)
        poly->basis.x--;
    else if (renderer->key(keys::rightArrow) && poly->basis.x + 64 < 512)
        poly->basis.x++;

    SDL_SetRenderDrawColor(renderer->rend, 0, 0, 0, 255);
    SDL_RenderClear(renderer->rend);

    SDL_SetRenderDrawColor(renderer->rend, 255, 255, 255, 255);
    SDL_RenderDrawLinesF(renderer->rend, *poly);

    fillPolygon(r, *poly, 0b1111'1111'0000'0000'0000'0000'1111'1111);

    return;
}

int main()
{
    BasicPoint points[] = {BasicPoint(0, 0),
                           BasicPoint(0, 128),
                           BasicPoint(64, 64)};

    poly = new Polygon2D(points, 3);
    poly->basis = BasicPoint(256, 256);

    renderer = new RenderWindow(512, 512, 8, update, SDL_WINDOW_OPENGL);
    renderer->mainLoop();

    delete poly;
    delete renderer;

    return 0;
}