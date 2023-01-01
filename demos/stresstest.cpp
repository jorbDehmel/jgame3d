#include "../jgame3d/jgame3d.hpp"
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
    int numCubes = 32;
    srand(time(NULL));

    dy = 1;
    dz = 5;

    Window wind(1028, 1028, 0, update);

    Model cube;
    createCube(cube, colorList);
    saveModel(cube, "cube.model");

    for (int i = 0; i < numCubes; i++)
    {
        Model cubeTemp = loadModel("cube.model");
        wind.add(cubeTemp);
    }

    vector<Model> &cubes = wind.getModels();
    for (int i = 0; i < cubes.size(); i++)
    {
        move(cubes[i], Point3D(rand() % 1000, rand() % 1000, (rand() % 512) + 512));
    }

    wind.mainLoop();

    return 0;
}
