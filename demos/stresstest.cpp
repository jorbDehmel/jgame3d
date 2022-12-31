#include "../jgame3d/basics.hpp"
#include "../jgame3d/window.hpp"
#include "../jgame3d/keys.hpp"
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

bool update(Window *wind)
{
    vector<Model> &cubes = wind->getModels();
    for (int i = 0; i < cubes.size(); i++)
    {
        rotate(cubes[i], getCenter(cubes[i]), Rotation((rand() % 100) / 1000.0, (rand() % 100) / 1000.0, (rand() % 100) / 1000.0));
        move(cubes[i], Point3D((rand() % 4) - 2.0, (rand() % 4) - 2.0, (rand() % 4) - 2.0));
    }

    return !wind->isKeyPressed(keys::esc);
}

int main()
{
    int numCubes = 8;
    srand(time(NULL));

    dy = 1;
    dz = 5;

    Window wind(128, 128, 0, update);
    wind.setUpScaleFactor(4);

    for (int i = 0; i < numCubes; i++)
    {
        Model cubeTemp;
        createCube(cubeTemp, colorList);
        wind.add(cubeTemp);
    }

    vector<Model> &cubes = wind.getModels();
    for (int i = 0; i < cubes.size(); i++)
    {
        move(cubes[i], Point3D(rand() % 128, rand() % 128, (rand() % 128) + 512));
    }

    wind.mainLoop();

    return 0;
}
