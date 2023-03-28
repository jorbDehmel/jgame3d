/*
Jordan "Jorb" Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2023 - present
GPLv3 held by author
*/

#include <iostream>
#include <jgame3d/jgame3d.hpp>
#include <jgame3d/keys.hpp>

using namespace std;

//////////////////////////////////////////////////

int stepSize = 5;
double cube_dy = 0, cube_dx = 0, cube_dz = 0;
Point3D cubePos(0, 0, 0);

bool update(Window *wind)
{
    Slicer *slicer = wind->getSlicer();

    if (wind->isKeyPressed(keys::esc))
    {
        return false;
    }

    if (wind->isKeyPressed(keys::w))
    {
        slicer->cameraPos.z -= stepSize;
    }
    else if (wind->isKeyPressed(keys::s))
    {
        slicer->cameraPos.z += stepSize;
    }

    if (wind->isKeyPressed(keys::a))
    {
        slicer->cameraPos.x += stepSize;
    }
    else if (wind->isKeyPressed(keys::d))
    {
        slicer->cameraPos.x -= stepSize;
    }

    if (wind->isKeyPressed(keys::leftArrow))
    {
        slicer->cameraRot.y += 0.01;
    }
    if (wind->isKeyPressed(keys::rightArrow))
    {
        slicer->cameraRot.y -= 0.01;
    }
    if (wind->isKeyPressed(keys::upArrow))
    {
        slicer->cameraRot.x -= 0.01;
    }
    if (wind->isKeyPressed(keys::downArrow))
    {
        slicer->cameraRot.x += 0.01;
    }

    if (wind->isKeyPressed(keys::r))
    {
        FOVScalar += 1;
    }
    else if (wind->isKeyPressed(keys::f))
    {
        FOVScalar -= 1;
    }

    if (wind->isKeyPressed(keys::q))
    {
        slicer->cameraPos.y -= stepSize;
    }
    else if (wind->isKeyPressed(keys::e))
    {
        slicer->cameraPos.y += stepSize;
    }

    return true;
}

int main()
{
    srand(time(NULL));

    SDL_DisplayMode dm;

    Window wind(256, 256, 0, update, SDL_WINDOW_OPENGL);

    assert(SDL_GetCurrentDisplayMode(0, &dm) == 0);

    wind.setUpScaleFactor((dm.h * .7) / 256);

    dz = 3;
    dy = 1;
    FOVScalar = 500;

    renderMinZ = FOVScalar / 2;
    renderMaxZ += FOVScalar * 5;

    for (int x = 0; x < 256 * 8; x += 256)
    {
        for (int y = 0; y < 256 * 8; y += 256)
        {
            Model tile;
            createSquare(tile, makeColor(255 - (y / 8), 255 - (y / 8), 255 - (y / 8), 255 - (y / 8)), 255);
            rotate(tile, Rotation(M_PI / 2, 0, 0));
            move(tile, Point3D(x, 300 + (rand() % 500), y));

            wind.add(tile);
        }
    }

    // Normal: About 7-30 fps
    // Experimental mode: About 15-60 fps
    // Wireframe: About 100-300 fps

    wind.getSlicer()->mode = SlicerModes::Wireframe;
    wind.mainLoop();

    return 0;
}
