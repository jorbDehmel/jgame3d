#include "objects.hpp"

/////////////////////////////////////////

Object::Object()
{
    shapes.clear();
    basis.x = basis.y = basis.z = 0;
    min = max = basis;
    rotationX = rotationY = rotationZ = 0;
}

void Object::add(Polygon3D other)
{
    Polygon3D temp = rotate(other);
    temp = move(temp);
    shapes.push_back(temp);
}

void Object::render(SDL_Renderer *renderer, Point3D &horizon)
{
    Polygon3D temp;
    for (int i = 0; i < shapes.size(); i++)
    {
        temp = shapes[i];
        temp.render(renderer, horizon);
    }
}

void Object::renderCross(SDL_Renderer *renderer, Point3D &horizon)
{
    // outpoly = globalmove(globalrotate(polymove(polyrotat(polygon))))
    for (int i = 0; i < shapes.size(); i++)
    {
        shapes[i].basis = basis;
        shapes[i].rotationX = rotationX;
        shapes[i].rotationY = rotationY;
        shapes[i].rotationZ = rotationZ;

        shapes[i].renderCross(renderer, horizon);
    }
}

Object move(const Object obj)
{
    throw runtime_error("UNIMPLEMENTED");
}

Object rotate(const Object obj)
{
    throw runtime_error("UNIMPLEMENTED");
}

/////////////////////////////////////////

GameSpace::GameSpace(int h, int w, int rt, void (*updateFunc)(vector<Object *> &), SDL_WindowFlags windowFlags)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    horizon.x = w / 2;
    horizon.y = h / 2;
    horizon.z = w;

    isRunning = true;
    assert(SDL_CreateWindowAndRenderer(w, h, windowFlags, &wind, &rend) == 0);
    refreshTime = rt;
    update = updateFunc;

    prevTicks = SDL_GetTicks();

    polygons.clear();

    return;
}

GameSpace::~GameSpace()
{
    kill();
}

/////////////////////////////////////////

void GameSpace::runFrame()
{
    prevTicks = SDL_GetTicks();

    update(polygons);

    SDL_RenderPresent(rend);

    passed = SDL_GetTicks() - prevTicks;
    cout << "Update took " << passed << " ms\n";
    if (refreshTime - passed > 0)
    {
        SDL_Delay(refreshTime - passed);
    }

    return;
}

void GameSpace::kill()
{
    isRunning = false;

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(wind);
}

void GameSpace::scanEvents()
{
    mouseState = SDL_BUTTON(SDL_GetRelativeMouseState(&mouseX, &mouseY));

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

bool GameSpace::key(int k) const
{
    return (keys.find(k) != keys.end());
}

void GameSpace::mainLoop()
{
    while (isRunning)
    {
        runFrame();
        scanEvents();
    }
    kill();

    return;
}

void GameSpace::addPolygon(Object *p)
{
    polygons.push_back(p);
    return;
}

void GameSpace::removePolygon(Object *p)
{
    for (int i = 0; i < polygons.size(); i++)
    {
        if (polygons[i] == p)
        {
            polygons.erase(polygons.begin() + i);
            return;
        }
    }
    return;
}

void GameSpace::removePolygons(bool (*checkingFunction)(const Object *))
{
    for (int i = 0; i < polygons.size(); i++)
    {
        if (checkingFunction(polygons[i]))
        {
            polygons.erase(polygons.begin() + i);
        }
    }
    return;
}

/////////////////////////////////////////
