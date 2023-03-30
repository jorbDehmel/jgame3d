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

    Object front = o;
    Object back = move(o, Point{0, 0, -100});

    Object bottom = move(rotate(o, Point{50, 50, 0}, Rotation{M_PI / 2, 0.01, 0}), Point{0, 50, -50});
    Object top = move(bottom, Point{0, -100, 0});

    Object left = rotate(o, Point{0, 50, 0}, Rotation{0, M_PI / 2, 0});
    Object right = move(left, Point{100, 0, 0});

    Object cube = merge({front, back, bottom, top, left, right});
    c.objects.push_back(cube);

    int numTriangles = 0;
    for (auto o : c.objects)
    {
        numTriangles += o.triangles.size();
    }
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