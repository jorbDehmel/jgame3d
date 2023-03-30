#include "../jtri.hpp"
#include "../../jgame3d/keys.hpp"
#include <iostream>
#include <chrono>
using namespace std;

int main()
{
    Camera c;
    c.cameraPos.z = 500;

    Triangle tri;
    tri.a = Point{0, 0, 0};
    tri.c = Point{100, 0, 0};
    tri.b = Point{100, 100, 0};
    tri.color = SDL_Color{255, 0, 0, 0};

    Object o;
    o.triangles.push_back(tri);
    o.triangles.push_back(rotate(tri, Point{50, 50, 0}, Rotation{0, 0, M_PI}));
    o.triangles.back().color.g = 255;
    o.offset.z = 500;

    Object tile = rotate(o, Point{50, 50, 0}, Rotation{M_PI / 2, 0.01, 0});
    c.objects.push_back(move(tile, Point{0, -50, 0}));

    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            c.objects.push_back(move(tile, Point{(double)50 * i, (double)i, (double)50 * j}));
        }
    }

    // Render
    SDL_Event event;
    bool running = true;
    while (running)
    {
        // auto start = chrono::high_resolution_clock::now();

        c.clear();
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

    return 0;
}