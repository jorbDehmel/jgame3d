#include "../jgame3d/basics.hpp"
#include "../jgame3d/keys.hpp"
#include "../jgame3d/window.hpp"

#include <set>

using namespace std;

//////////////////////////////////////////////////

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
        Point3D(32, 96, 0),
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
    //obj.polygons.push_back(left);

    //obj.polygons.push_back(top);
    //obj.polygons.push_back(bottom);

    //obj.polygons.push_back(front);
    //obj.polygons.push_back(back);

    move(obj, Point3D(128, 128, 256));

    return;
}

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
    
    if (wind->isKeyPressed(keys::p))
    {
        // Screenshot
        SDL_SaveBMP(SDL_GetWindowSurface(wind->getSpace()->wind), "screenshot.bmp");
    }

    return true;
}

int main()
{
    Window wind(512, 512, 8, update);

    Model cube;
    createCube(cube);

    wind.add(cube);

    wind.mainLoop();

    return 0;
}
