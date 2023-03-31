#include "../jgame3d/jgame3d.hpp"
#include <iostream>
#include <chrono>
using namespace std;

int main()
{
    srand(time(NULL));

    Camera c;
    c.cameraPos.z = 500;

    Triangle tri;
    tri.a = Point{0, 0, 0};
    tri.c = Point{100, 0, 0};
    tri.b = Point{100, 100, 0};
    tri.color = SDL_Color{128, 128, 128, 255};

    Object o;
    o.triangles.push_back(tri);
    o.triangles.push_back(rotate(tri, Point{50, 50, 0}, Rotation{0, 0, M_PI}));
    o.triangles.back().color.r = o.triangles.back().color.g = o.triangles.back().color.b = 64;
    o.offset.z = 500;

    Object tile = rotate(o, Point{50, 50, 0}, Rotation{M_PI / 2, 0.01, 0});

    double curY = 0;
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            curY += (rand() % 51) - 25;
            c.objects.push_back(move(tile, Point{(double)50 * i, (double)curY, (double)50 * j}));
            c.objects.back().rot = Rotation{drand(0, M_PI), drand(0, M_PI), drand(0, M_PI)};
        }
    }

    Object floor = mergeProject(c.objects);
    c.objects.clear();
    c.objects.push_back(floor);

    int numTriangles = 0;
    for (auto o : c.objects)
    {
        numTriangles += o.triangles.size();
    }
    cout << "Number of objects: " << c.objects.size() << '\n';
    cout << "Number of triangles: " << numTriangles << '\n';

    // Render
    SDL_Event event;
    bool running = true;

    int frames = 0;
    int startTime = time(NULL);
    while (running)
    {
        frames++;
        // auto start = chrono::high_resolution_clock::now();

        c.clear(SDL_Color{128, 128, 255, 255});
        c.update();
        c.present();

        // auto end = chrono::high_resolution_clock::now();
        // double elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        // cout << "ns: " << elapsed << " fps: " << 1'000'000'000 / elapsed << '\n';

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case 27:
                    running = false;
                    break;
                case 'e':
                    c.cameraPos.y += 10;
                    break;
                case 'q':
                    c.cameraPos.y -= 10;
                    break;
                case 'w':
                    c.cameraPos.z -= 10;
                    break;
                case 's':
                    c.cameraPos.z += 10;
                    break;
                case 'a':
                    c.cameraPos.x += 10;
                    break;
                case 'd':
                    c.cameraPos.x -= 10;
                    break;
                case keys::leftArrow:
                    c.cameraRot.y += 0.01;
                    break;
                case keys::rightArrow:
                    c.cameraRot.y -= 0.01;
                    break;
                case keys::upArrow:
                    c.cameraRot.x -= 0.01;
                    break;
                case keys::downArrow:
                    c.cameraRot.x += 0.01;
                    break;
                default:
                    cout << "Error: Unrecognized key " << event.key.keysym.sym << '\n';
                    break;
                }
            }
        }
    }
    int elapsedSeconds = time(NULL) - startTime;
    cout << "Frames: " << frames << '\n'
         << "Seconds: " << elapsedSeconds << '\n'
         << "Average FPS over session: " << (double)frames / elapsedSeconds << '\n';

    return 0;
}