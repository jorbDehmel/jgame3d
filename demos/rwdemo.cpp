/*
Jordan "Jorb" Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2022 - present
GPLv3 held by author
*/

#include "../jgame3d/jgame3d.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include "../jgame3d/keys.hpp"
#include <iostream>
using namespace std;

//////////////////////////////////////////////////

vector<SDL_Color> colorList = {
    makeColor(255, 0, 0, 255),
    makeColor(0, 255, 0, 255),
    makeColor(0, 0, 255, 255),
    makeColor(255, 255, 0, 255),
    makeColor(255, 0, 255, 255),
    makeColor(0, 255, 255, 255)};

//////////////////////////////////////////////////

int stepSize = 5;
double cube_dy = 0, cube_dx = 0, cube_dz = 0;
Point3D cubePos(0, 0, 0);

bool update(Window *wind)
{
    SDL_SetRenderDrawColor(wind->getRenderer(), 255, 255, 255, 255);
    SDL_RenderDrawLineF(wind->getRenderer(), 0, 0, 1000, 1000);
    SDL_RenderDrawLineF(wind->getRenderer(), 0, 1000, 1000, 0);

    Model &cube = wind->getModels()[0];

    if (wind->isKeyPressed(keys::esc))
    {
        return false;
    }

    if (wind->isKeyPressed(keys::w))
    {
        if (cube.polygons[0].points[0].y > renderMinY)
            move(cube, Point3D(0, -stepSize, 0));
    }
    if (wind->isKeyPressed(keys::s))
    {
        if (cube.polygons[0].points[0].y < renderMaxY)
            move(cube, Point3D(0, stepSize, 0));
    }

    if (wind->isKeyPressed(keys::q))
        cube_dz++;
    else if (wind->isKeyPressed(keys::e))
        cube_dz--;
    else
    {
        if (cube_dz < 0)
            cube_dz++;
        else if (cube_dz > 0)
            cube_dz--;
    }

    if (wind->isKeyPressed(keys::d))
        cube_dx++;
    else if (wind->isKeyPressed(keys::a))
        cube_dx--;
    else
    {
        if (cube_dx < 0)
            cube_dx++;
        else if (cube_dx > 0)
            cube_dx--;
    }

    if (wind->isKeyPressed(keys::upArrow))
        rotate(cube, Rotation(.01, 0, 0));
    if (wind->isKeyPressed(keys::downArrow))
        rotate(cube, Rotation(0, .01, 0));
    if (wind->isKeyPressed(keys::leftArrow))
        rotate(cube, Rotation(0, 0, .01));

    if (wind->isKeyPressed(keys::r))
        FOVScalar += 1;
    else if (wind->isKeyPressed(keys::f))
        FOVScalar -= 1;

    if (cube_dx > 0 && cube.polygons[0].points[0].x < renderMaxX)
    {
        move(cube, Point3D(cube_dx, 0, 0));
    }
    else if (cube_dx < 0 && cube.polygons[0].points[0].x > renderMinX)
    {
        move(cube, Point3D(cube_dx, 0, 0));
    }
    else
    {
        cube_dx = 0;
    }

    if (cube_dz > 0 && cube.polygons[0].points[0].z + 64 < renderMaxZ)
    {
        move(cube, Point3D(0, 0, cube_dz));
    }
    else if (cube_dz < 0 && cube.polygons[0].points[0].z > renderMinZ)
    {
        move(cube, Point3D(0, 0, cube_dz));
    }
    else
    {
        cube_dz = 0;
    }

    // wind->getSlicer()->cameraRot.y -= .001;

    return true;
}

int main()
{
    SDL_DisplayMode dm;

    Window wind(1028, 1028, 0, update, SDL_WINDOW_OPENGL);

    assert(SDL_GetCurrentDisplayMode(0, &dm) == 0);

    wind.setUpScaleFactor((dm.h * .7) / 1028);

    dz = 3;
    FOVScalar = 500;

    renderMinZ = FOVScalar;
    renderMaxZ += FOVScalar;

    Model cube;
    createCube(cube, colorList, 128);
    move(cube, Point3D(500, 500, 600));

    wind.add(cube);

    wind.mainLoop();

    return 0;
}
