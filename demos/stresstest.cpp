#include "../jgame3d/basics.hpp"
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
    obj.polygons.push_back(left);

    obj.polygons.push_back(top);
    obj.polygons.push_back(bottom);

    obj.polygons.push_back(front);
    obj.polygons.push_back(back);

    move(obj, Point3D(0, 0, 256));

    return;
}

//////////////////////////////////////////////////

bool hasKey(set<SDL_Keycode> &set, int keycode)
{
    return set.count(keycode) != 0;
}

int main()
{
    int numCubes = 32;
    srand(time(NULL));

    /*
    cubes|polygons|ms/frame
    1     (6)      1-10
    32    (192)    40-50
    64    (384)    70-110
    128   (768)    140-170
    256   (1536)   325-400
    */

    //////////////////

    set<SDL_Keycode> keys;

    dz = dy = 1;

    SDL_Window *wind;
    SDL_Renderer *rend;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_CreateWindowAndRenderer(256, 256, SDL_WINDOW_OPENGL, &wind, &rend);
    SDL_SetWindowSize(wind, 1028, 1028);
    SDL_RenderSetScale(rend, 4, 4);

    horizon.x = horizon.y = 128;
    horizon.z = 1000;

    Renderer space(rend, wind);

    Model cubes[numCubes];

    for (int i = 0; i < numCubes; i++)
    {
        createCube(cubes[i]);
        space.models.push_back(&cubes[i]);

        move(cubes[i], Point3D(rand() % 256, rand() % 256, rand() % 256));
    }

    int delayTime = 0;
    double stepSize = 1;

    int timeA, timeB, ellapsed;

    SDL_Event event;
    bool isRunning = true;
    while (isRunning)
    {
        timeA = SDL_GetTicks();

        SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
        SDL_RenderClear(rend);

        for (int i = 0; i < numCubes; i++)
        {
            rotate(cubes[i], Rotation((rand() % 100) / 1000.0, (rand() % 100) / 1000.0, (rand() % 100) / 1000.0));
            move(cubes[i], Point3D((rand() % 10) - 5, (rand() % 10) - 5, (rand() % 10) - 5));
        }

        space.render();

        SDL_RenderPresent(rend);

        ///////////////////////////

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                keys.insert(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                keys.erase(event.key.keysym.sym);
                break;
            }
        }

        //////////////////////////////

        if (!keys.empty())
        {
            if (hasKey(keys, 27))
            {
                isRunning = false;
                break;
            }
        }

        //////////////////////////////

        timeB = SDL_GetTicks();
        ellapsed = timeB - timeA;

        if (ellapsed < delayTime)
        {
            SDL_Delay(delayTime - ellapsed);
        }
        else
        {
            cout << "Update took " << ellapsed << " ms\n";
        }
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(wind);
    SDL_Quit();

    return 0;
}
