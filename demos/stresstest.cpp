#include "../jgame3d/basics.hpp"
#include "../jgame3d/window.hpp"
#include "../jgame3d/keys.hpp"

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

    return;
}

//////////////////////////////////////////////////

bool update(Window *wind)
{
    vector<Model> &cubes = wind->getModels();
    for (int i = 0; i < cubes.size(); i++)
    {
        rotate(cubes[i], getCenter(cubes[i]), Rotation((rand() % 100) / 1000.0, (rand() % 100) / 1000.0, (rand() % 100) / 1000.0));
        move(cubes[i], Point3D((rand() % 10) - 5, (rand() % 10) - 5, (rand() % 10) - 5));
    }

    return !wind->isKeyPressed(keys::esc);
}

int main()
{
    int numCubes = 8;
    srand(time(NULL));

    dy = 1;
    dz = 5;

    Window wind(512, 512, 0, update);

    for (int i = 0; i < numCubes; i++)
    {
        Model cubeTemp;
        createCube(cubeTemp);
        wind.add(cubeTemp);
    }

    vector<Model> &cubes = wind.getModels();
    for (int i = 0; i < cubes.size(); i++)
    {
        move(cubes[i], Point3D(rand() % 512, rand() % 512, (rand() % 256) + 256));
    }

    wind.mainLoop();

    return 0;
}
