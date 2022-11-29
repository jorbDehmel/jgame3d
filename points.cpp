#include "points.hpp"

/////////////////////////////////////////

Polygon2D::Polygon2D(BasicPoint pointsIn[], int num)
{
    for (int i = 0; i < num; i++)
    {
        points.push_back(pointsIn[i]);
    }
    return;
}

SDL_FPoint *Polygon2D::SDLify()
{
    assert(points.size() >= 1);

    SDL_FPoint *out = new SDL_FPoint[points.size() + 1];

    for (int i = 0; i < points.size(); i++)
    {
        out[i].x = points[i].x;
        out[i].y = points[i].y;
    }
    out[points.size()].x = points[0].x;
    out[points.size()].y = points[0].y;

    return out;
}

int SDL_RenderDrawLinesF(SDL_Renderer *renderer, Polygon2D &polygon)
{
    return SDL_RenderDrawLinesF(renderer, polygon.SDLify(), polygon.points.size() + 1);
}

/////////////////////////////////////////

void move(Polygon2D &poly, BasicPoint by)
{
    for (int i = 0; i < poly.points.size(); i++)
    {
        poly.points[i].x += by.x;
        poly.points[i].y += by.y;
    }
    return;
}

void rotate(Polygon2D &poly, double degree, BasicPoint about)
{
    move(poly, BasicPoint(-about.x, -about.y));

    double newX, newY;

    double c = cos(degree);
    double s = sin(degree);

    for (int i = 0; i < poly.points.size(); i++)
    {
        newX = (c * poly.points[i].x) + (-s * poly.points[i].y);
        newY = (s * poly.points[i].x) + (c * poly.points[i].y);

        poly.points[i].x = newX;
        poly.points[i].y = newY;
    }

    move(poly, about);

    return;
}

/////////////////////////////////////////

RenderWindow::RenderWindow(int h, int w, int rt, void (*update)(SDL_Renderer *), SDL_WindowFlags windowFlags)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    isRunning = true;
    assert(SDL_CreateWindowAndRenderer(w, h, windowFlags, &wind, &rend) == 0);
    refreshTime = rt;
    updateFunc = update;

    prevTicks = SDL_GetTicks();
}

RenderWindow::~RenderWindow()
{
    kill();

    SDL_Quit();
}

/////////////////////////////////////////

void RenderWindow::scanEvents()
{
    mouseState = SDL_BUTTON(SDL_GetRelativeMouseState(&mouseX, &mouseY));

    keys.clear();

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
        {
            if (keys.find(event.key.keysym.sym) == keys.end())
            {
                keys.insert(event.key.keysym.sym);
            }
        }
        else if (event.type == SDL_KEYUP)
        {
            if (keys.find(event.key.keysym.sym) != keys.end())
            {
                keys.erase(event.key.keysym.sym);
            }
        }
    }

    return;
}

void RenderWindow::runFrame()
{
    prevTicks = SDL_GetTicks();

    updateFunc(rend);
    SDL_RenderPresent(rend);

    passed = SDL_GetTicks() - prevTicks;
    if (refreshTime - passed > 0)
    {
        SDL_Delay(refreshTime - passed);
    }

    return;
}

void RenderWindow::mainLoop()
{
    while (isRunning)
    {
        runFrame();
        scanEvents();
    }
    kill();

    return;
}

void RenderWindow::kill()
{
    isRunning = false;

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(wind);
}

bool RenderWindow::key(int k) const
{
    return (keys.find(k) != keys.end());
}

/////////////////////////////////////////
