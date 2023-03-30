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
    o.offset.z = 500;

    c.objects.push_back(o);

    // Render
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

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == 27)
                {
                    running = false;
                }
                else if (event.key.keysym.sym == ' ')
                {
                    c.cameraPos.x = c.cameraPos.y = c.cameraPos.z = 0;
                    c.cameraRot.x = c.cameraRot.y = c.cameraRot.z = 0;
                }

                else if (event.key.keysym.sym == 'e')
                {
                    c.cameraPos.z += 10;
                    cout << c.cameraPos.z << '\n';
                }
                else if (event.key.keysym.sym == 'q')
                {
                    c.cameraPos.z -= 10;
                    cout << c.cameraPos.z << '\n';
                }
                else if (event.key.keysym.sym == 'w')
                {
                    c.cameraPos.y -= 10;
                }
                else if (event.key.keysym.sym == 's')
                {
                    c.cameraPos.y += 10;
                }
                else if (event.key.keysym.sym == 'a')
                {
                    c.cameraPos.x -= 10;
                }
                else if (event.key.keysym.sym == 'd')
                {
                    c.cameraPos.x += 10;
                }

                else if (event.key.keysym.sym == keys::leftArrow)
                {
                    c.objects[0].rot.x += 0.01;
                    cout << c.objects[0].rot.x << '\n';
                    // c.cameraRot.x += 0.001;
                    // cout << c.cameraRot.x << '\n';
                }
                else if (event.key.keysym.sym == keys::rightArrow)
                {
                    c.objects[0].rot.x -= 0.01;
                    cout << c.objects[0].rot.x << '\n';
                    // c.cameraRot.x -= 0.001;
                    // cout << c.cameraRot.x << '\n';
                }

                else
                {
                    cout << "Unrecognized key " << (int)event.key.keysym.sym << '\n';
                }
            }
        }
    }

    return 0;
}