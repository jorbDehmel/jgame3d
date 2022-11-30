#include "points3d.hpp"

/////////////////////////////////////////

#define FOV_SCALAR 1
const Point3D horizon(256, 256, 512);

/////////////////////////////////////////

Polygon3D::Polygon3D(Point3D pointsIn[], int num)
{
    for (int i = 0; i < num; i++)
    {
        points.push_back(pointsIn[i]);
    }
    return;
}

SDL_FPoint *Polygon3D::SDLify() const
{
    assert(points.size() >= 1);

    SDL_FPoint *out = new SDL_FPoint[points.size() + 1];

    for (int i = 0; i < points.size(); i++)
    {
        out[i].x = points[i].x - horizon.x;
        out[i].y = points[i].y - horizon.y;

        // Calculate
        out[i].x *= 1 + ((horizon.z - (points[i].z * FOV_SCALAR)) / (points[i].z * FOV_SCALAR));
        out[i].y *= 1 + ((horizon.z - (points[i].z * FOV_SCALAR)) / (points[i].z * FOV_SCALAR));

        out[i].x += horizon.x;
        out[i].y += horizon.y;
    }
    out[points.size()].x = out[0].x;
    out[points.size()].y = out[0].y;

    return out;
}

void Polygon3D::operator+=(Polygon3D &other)
{
    for (auto point : other.points)
    {
        points.push_back(point);
    }
    return;
}

/////////////////////////////////////////

int SDL_RenderDrawLinesF(SDL_Renderer *renderer, const Polygon3D polygon)
{
    if (polygon.basis.z > horizon.z)
    {
        return 0;
    }

    Polygon3D temp = rotate(polygon);
    temp = move(temp);

    return SDL_RenderDrawLinesF(renderer, temp.SDLify(), temp.points.size() + 1);
}

void crossDrawLines(SDL_Renderer *renderer, const Polygon3D &polygon)
{
    if (polygon.basis.z > horizon.z)
    {
        return;
    }
    Polygon3D temp = rotate(polygon);
    temp = move(temp);

    SDL_FPoint a, b;
    auto points = temp.SDLify();

    for (int i = 0; i < temp.points.size(); i++)
    {
        for (int j = i; j < temp.points.size(); j++)
        {
            a.x = points[i].x;
            a.y = points[i].y;

            b.x = points[j].x;
            b.y = points[j].y;

            SDL_RenderDrawLineF(renderer, a.x, a.y, b.x, b.y);
        }
    }
    return;
}

Polygon3D move(const Polygon3D poly)
{
    Polygon3D out = poly;
    for (int i = 0; i < poly.points.size(); i++)
    {
        out.points[i].x += poly.basis.x;
        out.points[i].y += poly.basis.y;
        out.points[i].z += poly.basis.z;
    }
    return out;
}

Polygon3D rotate(const Polygon3D p)
{
    Polygon3D out = p;

    out.basis.x = 0;
    out.basis.y = 0;
    out.basis.z = 0;
    out = move(out);

    for (int i = 0; i < out.points.size(); i++)
    {
        rotatePoint(out.points[i], out.rotationX, out.rotationY, out.rotationZ);
    }

    out.basis = p.basis;
    out = move(out);

    return out;
}

void rotatePoint(Point3D &p, double dx = 0, double dy = 0, double dz = 0)
{
    double s, c;
    double x, y, z;

    if (dx != 0)
    {
        s = sin(dx), c = cos(dx);
        x = p.x, y = p.y, z = p.z;

        p.y = (c * y) - (s * z);
        p.z = (s * y) + (c * z);
    }

    if (dy != 0)
    {
        s = sin(dy), c = cos(dy);
        x = p.x, y = p.y, z = p.z;

        p.x = (c * x) + (s * z);
        p.z = (s * -x) + (c * z);
    }

    if (dz != 0)
    {
        s = sin(dz), c = cos(dz);
        x = p.x, y = p.y, z = p.z;

        p.x = (c * x) - (s * y);
        p.y = (s * x) + (c * y);
    }

    return;
}

/////////////////////////////////////////

GameSpace::GameSpace(int h, int w, int rt, void (*updateFunc)(vector<Polygon3D> &), SDL_WindowFlags windowFlags)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    isRunning = true;
    assert(SDL_CreateWindowAndRenderer(w, h, windowFlags, &wind, &rend) == 0);
    refreshTime = rt;
    updateFunc = update;

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

    for (int i = 0; i < polygons.size(); i++)
    {
        SDL_RenderDrawLinesF(rend, polygons[i]);
    }

    SDL_RenderPresent(rend);

    passed = SDL_GetTicks() - prevTicks;
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

void GameSpace::addPolygon(Polygon3D p)
{
    polygons.push_back(p);
    return;
}

void GameSpace::removePolygon(Polygon3D *p)
{
    for (int i = 0; i < polygons.size(); i++)
    {
        if (&polygons[i] == p)
        {
            polygons.erase(polygons.begin() + i);
            return;
        }
    }
    return;
}

void GameSpace::removePolygons(bool (*checkingFunction)(const Polygon3D &))
{
    for (auto i = polygons.begin(); i != polygons.end(); i++)
    {
        if (checkingFunction(*i))
        {
            polygons.erase(i);
        }
    }
    return;
}

/////////////////////////////////////////
