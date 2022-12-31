#include "../jgame3d/basics.hpp"
#include "../jgame3d/keys.hpp"
#include "../jgame3d/window.hpp"
#include "../jgame3d/resources.hpp"

#include <set>

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

int stepSize = 1;
bool update(Window *wind)
{
    Model &cube = wind->getModels()[0];

    if (wind->isKeyPressed(keys::esc))
    {
        return false;
    }

    if (wind->isKeyPressed(keys::q))
        move(cube, Point3D(0, 0, stepSize));
    if (wind->isKeyPressed(keys::e))
        move(cube, Point3D(0, 0, -stepSize));

    if (wind->isKeyPressed(keys::w))
        move(cube, Point3D(0, -stepSize, 0));
    if (wind->isKeyPressed(keys::s))
        move(cube, Point3D(0, stepSize, 0));

    if (wind->isKeyPressed(keys::d))
        move(cube, Point3D(stepSize, 0, 0));
    if (wind->isKeyPressed(keys::a))
        move(cube, Point3D(-stepSize, 0, 0));

    if (wind->isKeyPressed(keys::upArrow))
        rotate(cube, Rotation(.01, 0, 0));
    if (wind->isKeyPressed(keys::downArrow))
        rotate(cube, Rotation(0, .01, 0));
    if (wind->isKeyPressed(keys::leftArrow))
        rotate(cube, Rotation(0, 0, .01));

    return true;
}

int main()
{
    dz = 3;

    Window wind(1028, 1028, 10, update, SDL_WINDOW_OPENGL);

    Model cube;
    createCube(cube, colorList);
    move(cube, Point3D(500, 500, 250));
    wind.add(cube);

    wind.mainLoop();

    return 0;
}
