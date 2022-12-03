#include "../jgame3D/jgame3D.hpp"
#include <iostream>
using namespace std;

void update(SDL_Renderer *rend)
{
}

int main()
{
    RenderWindow rend(512, 512, 0, update, SDL_VIDEO_OPENGL);
    rend.mainLoop();

    return 0;
}
