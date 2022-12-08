#include "../jgame3D/jgame3D.hpp"
#include <iostream>
using namespace std;

Polygon2D *poly;
RenderWindow *renderer;

void update(SDL_Renderer *r)
{
    if (renderer->key(keys::esc))
        renderer->isRunning = false;

    if (renderer->key(keys::upArrow) && poly->basis.y > 64)
        poly->basis.y--;
    else if (renderer->key(keys::downArrow) && poly->basis.y + 64 < 512)
        poly->basis.y++;
    if (renderer->key(keys::leftArrow) && poly->basis.x > 64)
        poly->basis.x--;
    else if (renderer->key(keys::rightArrow) && poly->basis.x + 64 < 512)
        poly->basis.x++;

    SDL_SetRenderDrawColor(renderer->rend, 0, 0, 0, 255);
    SDL_RenderClear(renderer->rend);

    fillPolygon(r, *poly, Pixel(255, 0, 0, 255));

    poly->rotation += 0.01;

    return;
}

int main()
{
    BasicPoint points[4] = {
        BasicPoint(0, -50),
        BasicPoint(200, 0),
        BasicPoint(0, 50),
        BasicPoint(50, 0)};

    poly = new Polygon2D(points, 4);
    poly->basis = BasicPoint(256, 256);

    renderer = new RenderWindow(512, 512, 8, update, SDL_WINDOW_OPENGL);
    renderer->mainLoop();

    delete poly;
    delete renderer;

    return 0;
}