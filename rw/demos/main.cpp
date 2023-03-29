#include "../jtri.hpp"
#include <iostream>
#include <chrono>
using namespace std;

int main()
{
    Camera c;
    c.cameraPos.z = 500;

    Triangle tri;
    tri.a = Point{50, 200, 0};
    tri.c = Point{400, 250, -50};
    tri.b = Point{300, 400, 50};
    tri.color = SDL_Color{255, 0, 0, 0};

    Object o;
    o.triangles.push_back(tri);
    c.objects.push_back(o);
    o.offset.z = 500;

    c.objects.push_back(o);

    // Render
    bool running = true;
    auto start = chrono::high_resolution_clock::now();
    while (running)
    {
        c.clear();
        c.update();
        c.present();

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
                else if (event.key.keysym.sym == 's')
                {
                    c.cameraPos.z++;
                    cout << c.cameraPos.z << '\n';
                }
                else if (event.key.keysym.sym == 'w')
                {
                    c.cameraPos.z--;
                    cout << c.cameraPos.z << '\n';
                }
                else if (event.key.keysym.sym == 'a')
                {
                    c.cameraRot.x += 0.001;
                    cout << c.cameraRot.x << '\n';
                }
                else if (event.key.keysym.sym == 'd')
                {
                    c.cameraRot.x -= 0.001;
                    cout << c.cameraRot.x << '\n';
                }
                else
                {
                    cout << "Unrecognized key " << (int)event.key.keysym.sym << '\n';
                }
            }
        }
    }
    auto end = chrono::high_resolution_clock::now();
    double elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    cout << "ns: " << elapsed << '\n'
         << "fps: " << 1'000'000'000'000 / elapsed << '\n';

    return 0;
}