#include "points3d.hpp"

/////////////////////////////////////////

int FOV_SCALAR = 1;

/////////////////////////////////////////

Polygon3D::Polygon3D(Point3D pointsIn[], int num)
{
    for (int i = 0; i < num; i++)
    {
        points.push_back(pointsIn[i]);
    }
    return;
}

SDL_FPoint *Polygon3D::SDLify(Point3D &horizon)
{
    assert(points.size() >= 1);

    min = max = points[0];
    for (Point3D p : points)
    {
        if (p.x < min.x)
            min.x = p.x;
        if (p.x > max.x)
            max.x = p.x;
        if (p.y < min.y)
            min.y = p.y;
        if (p.y > max.y)
            max.y = p.y;
        if (p.z < min.z)
            min.z = p.z;
        if (p.z > max.z)
            max.z = p.z;
    }

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

void Polygon3D::render(SDL_Renderer *renderer, Point3D &horizon)
{
    cout << "Polygon render called\n";

    if (basis.z > horizon.z || basis.z < 0)
    {
        return;
    }

    Polygon3D temp = rotate(*this);
    temp = move(temp);

    SDL_RenderDrawLinesF(renderer, temp.SDLify(horizon), temp.points.size() + 1);

    return;
}

void Polygon3D::renderCross(SDL_Renderer *renderer, Point3D &horizon)
{
    if (basis.z > horizon.z || basis.z < 0)
    {
        return;
    }

    Polygon3D temp = rotate(*this);
    temp = move(temp);

    SDL_FPoint a, b;
    auto points = temp.SDLify(horizon);

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

void Object::render(SDL_Renderer *renderer, Point3D &horizon)
{
    min = max = shapes[0].min;
    for (int i = 0; i < shapes.size(); i++)
    {
        shapes[i].render(renderer, horizon);

        if (shapes[i].min.x < min.x)
            min.x = shapes[i].min.x;
        if (shapes[i].max.x > max.x)
            max.x = shapes[i].max.x;
        if (shapes[i].min.y < min.y)
            min.y = shapes[i].min.y;
        if (shapes[i].max.y > max.y)
            max.y = shapes[i].max.y;
        if (shapes[i].min.z < min.z)
            min.z = shapes[i].min.z;
        if (shapes[i].max.z > max.z)
            max.z = shapes[i].max.z;
    }

    return;
}

void Object::renderCross(SDL_Renderer *renderer, Point3D &horizon)
{
    for (int i = 0; i < shapes.size(); i++)
    {
        shapes[i].renderCross(renderer, horizon);
    }

    return;
}

///////////////////////////////////////////////////////////////

Polygon3D move(const Polygon3D poly)
{
    Polygon3D out = poly;
    for (int i = 0; i < out.points.size(); i++)
    {
        out.points[i].x += poly.basis.x;
        out.points[i].y += poly.basis.y;
        out.points[i].z += poly.basis.z;
    }
    return out;
}

Object move(const Object obj)
{
    Object out = obj;
    for (int i = 0; i < out.shapes.size(); i++)
    {
        out.shapes[i].basis = obj.basis;
        move(out.shapes[i]);
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

Object rotate(const Object obj)
{
    Object out = obj;
    for (int i = 0; i < out.shapes.size(); i++)
    {
        out.shapes[i].rotationX = obj.rotationX;
        out.shapes[i].rotationY = obj.rotationY;
        out.shapes[i].rotationZ = obj.rotationZ;

        rotate(out.shapes[i]);
    }
    return out;
}

///////////////////////////////////////////////////////////////

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

GameSpace::GameSpace(int h, int w, int rt, void (*updateFunc)(vector<Polygon3D *> &), SDL_WindowFlags windowFlags)
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

    for (int i = 0; i < polygons.size(); i++)
    {
        polygons[i]->renderCross(rend, horizon);
    }

    SDL_RenderPresent(rend);

    passed = SDL_GetTicks() - prevTicks;
    if (refreshTime - passed > 0)
    {
        // cout << "Calculations took " << passed << " ms\n";
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

void GameSpace::addPolygon(Polygon3D *p)
{
    polygons.push_back(p);
    return;
}

void GameSpace::removePolygon(Polygon3D *p)
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

void GameSpace::removePolygons(bool (*checkingFunction)(const Polygon3D *))
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
