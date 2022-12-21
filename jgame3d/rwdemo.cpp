#include "basics.hpp"
using namespace std;

//////////////////////////////////////////////////

SDL_Color makeColor(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
{
    SDL_Color out;
    out.r = r;
    out.g = g;
    out.b = b;
    out.a = a;
    return out;
}

vector<SDL_Color> colors = {
    makeColor(255, 0, 0, 255),
    makeColor(0, 255, 0, 255),
    makeColor(0, 0, 255, 255),
    makeColor(255, 255, 0, 255),
    makeColor(255, 0, 255, 255),
    makeColor(0, 255, 255, 255)};

//////////////////////////////////////////////////

void createCube(Model &obj)
{
    vector<Point3D> tbSquare = {
        Point3D(0, 0, 0),
        Point3D(64, 0, 0),
        Point3D(64, 64, 0),
        Point3D(0, 64, 0)};

    Polygon top;
    top.points = tbSquare;
    top.color = colors[0];
    move(top, Point3D(-32, -32, 32));

    Polygon bottom;
    bottom.points = tbSquare;
    bottom.color = colors[1];
    move(bottom, Point3D(-32, -32, -32));

    /////////////////////////////

    vector<Point3D> lrSquare = {
        Point3D(0, 0, 0),
        Point3D(0, 64, 0),
        Point3D(0, 64, 64),
        Point3D(0, 0, 64)};

    Polygon right;
    right.points = lrSquare;
    right.color = colors[2];
    move(right, Point3D(32, -32, -32));

    Polygon left;
    left.points = lrSquare;
    left.color = colors[3];
    move(left, Point3D(-32, -32, -32));

    ////////////////////

    vector<Point3D> fbSquare = {
        Point3D(0, 0, 0),
        Point3D(64, 0, 0),
        Point3D(64, 0, 64),
        Point3D(0, 0, 64)};

    Polygon front;
    front.points = fbSquare;
    front.color = colors[4];
    move(front, Point3D(-32, 32, -32));

    Polygon back;
    back.points = fbSquare;
    back.color = colors[5];
    move(back, Point3D(-32, -32, -32));

    obj.polygons.push_back(right);
    obj.polygons.push_back(left);

    obj.polygons.push_back(top);
    obj.polygons.push_back(bottom);

    obj.polygons.push_back(front);
    obj.polygons.push_back(back);

    move(obj, Point3D(256, 256, 256));

    return;
}

Point3D getCenter(const Model &m)
{
    double minX, maxX, minY, maxY, minZ, maxZ;
    minX = maxX = m.polygons[0].points[0].x;
    minY = maxY = m.polygons[0].points[0].y;
    minZ = maxZ = m.polygons[0].points[0].z;

    for (auto poly : m.polygons)
    {
        for (auto point : poly.points)
        {
            if (point.x < minX)
                minX = point.x;
            else if (point.x > maxX)
                maxX = point.x;

            if (point.y < minY)
                minY = point.y;
            else if (point.y > maxY)
                maxY = point.y;

            if (point.z < minZ)
                minZ = point.z;
            else if (point.z > maxZ)
                maxZ = point.z;
        }
    }

    Point3D out;

    out.x = minX + ((maxX - minX) / 2);
    out.y = minY + ((maxY - minY) / 2);
    out.z = minZ + ((maxZ - minZ) / 2);

    return out;
}

//////////////////////////////////////////////////

int main()
{
    dz = 1;

    SDL_Window *wind;
    SDL_Renderer *rend;

    assert(SDL_CreateWindowAndRenderer(512, 512, SDL_WINDOW_OPENGL, &wind, &rend) == 0);
    SDL_SetWindowSize(wind, 1028, 1028);
    SDL_RenderSetScale(rend, 2, 2);

    horizon.x = horizon.y = 256;
    horizon.z = 1000;

    Renderer space(rend, wind);
    assert(space.rend == rend);

    Model cube;
    createCube(cube);
    space.models.push_back(&cube);

    int delayTime = 8;

    int timeA, timeB, ellapsed;

    SDL_Event event;
    bool isRunning = true;
    while (isRunning)
    {
        timeA = SDL_GetTicks();

        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderClear(rend);

        rotate(cube, getCenter(cube), Point3D(.005, .005, .005));

        space.render();

        SDL_RenderPresent(rend);

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == 27)
                    isRunning = false;
                else if (event.key.keysym.sym == 'w')
                    move(cube, Point3D(0, 0, 5));
                else if (event.key.keysym.sym == 's')
                    move(cube, Point3D(0, 0, -5));

                break;
            default:
                break;
            }
        }

        timeB = SDL_GetTicks();
        ellapsed = timeB - timeA;

        if (ellapsed < delayTime)
        {
            SDL_Delay(delayTime - ellapsed);
        }
    }

    return 0;
}
