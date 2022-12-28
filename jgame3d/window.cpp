#include "window.hpp"

SDL_Point mousePos;
Uint32 mouseState = 0;

Window::Window(int W, int H, int RefreshRate, bool (*Update)(Window *space))
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(W, H, SDL_WINDOW_OPENGL, &wind, &rend);

    update = Update;

    horizon.x = W / 2;
    horizon.y = H / 2;
    horizon.z = W * 2;

    space = new Renderer(rend, wind);

    delayTime = RefreshRate;
}

Window::~Window()
{
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(wind);
    SDL_Quit();

    return;
}

void Window::mainLoop()
{
    Uint32 start, end;
    SDL_Event event;

    bool isRunning = true;
    while (isRunning)
    {
        // Get initial time for later delaying
        start = SDL_GetTicks();

        // Update
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
        SDL_RenderClear(rend);

        space->render();
        SDL_RenderPresent(rend);

        isRunning = update(this);

        // Poll keyboard
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                // cout << "Keypress " << (int)event.key.keysym.sym << '\n';
                keys.insert(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                keys.erase(event.key.keysym.sym);
                break;
            default:
                break;
            }
        }

        // Update mouse position and state
        mouseState = SDL_GetMouseState(&mousePos.x, &mousePos.y);

        // Delay if needed
        end = SDL_GetTicks();
        if (end - start < delayTime)
        {
            SDL_Delay(delayTime - (end - start));
        }
        else
        {
            cout << "Update took " << end - start << " ms\n";
        }
    }
}

bool Window::isKeyPressed(const int &key) const
{
    if (keys.empty())
    {
        return false;
    }
    else
    {
        return keys.count(key) != 0;
    }
}

void Window::add(Polygon &p)
{
    Model temp;
    temp.polygons.push_back(p);
    space->models.push_back(temp);
    return;
}

void Window::add(Model &m)
{
    space->models.push_back(m);
    return;
}

vector<Model> &Window::getModels() const
{
    return space->models;
}

SDL_Window *Window::getWindow()
{
    return wind;
}

SDL_Renderer *Window::getRenderer()
{
    return rend;
}

Renderer *Window::getSpace()
{
    return space;
}