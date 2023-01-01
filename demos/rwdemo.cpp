#include "../jgame3d/jgame3d.hpp"
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
    else if (wind->isKeyPressed(keys::s))
        move(cube, Point3D(0, stepSize, 0));
    else
    {
        if (cube.polygons[0].points[0].y < renderMaxY)
        {
            cube_dy += 1;
            move(cube, Point3D(0, cube_dy, 0));
        }
        else
        {
            cube_dy = 0;
        }
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

    if (cube_dx > 0 && cube.polygons[0].points[0].x + 64 < renderMaxX)
    {
        move(cube, Point3D(cube_dx, 0, 0));
    }
    else if (cube_dx < 0 && cube.polygons[0].points[0].x - 64 > renderMinX)
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
    else if (cube_dz < 0 && cube.polygons[0].points[0].z - 64 > renderMinZ)
    {
        move(cube, Point3D(0, 0, cube_dz));
    }
    else
    {
        cube_dz = 0;
    }

    return true;
}

int main()
{
    dz = 3;

    Window wind(1028, 1028, 10, update, SDL_WINDOW_OPENGL);

    Model cube;
    createCube(cube, colorList);

    // saveModel(cube, "cube.model");
    // cube = loadModel("cube.model");

    move(cube, Point3D(500, 500, 500));

    wind.add(cube);

    wind.mainLoop();

    return 0;
}
