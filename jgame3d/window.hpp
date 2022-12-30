#ifndef WINDOW_H
#define WINDOW_H

#include "basics.hpp"
#include <set>

extern SDL_Point mousePos;
extern Uint32 mouseState;

class Window
{
public:
    Window(int W, int H, int RefreshRate, bool (*Update)(Window *space),
           SDL_WindowFlags Flags = SDL_WINDOW_OPENGL);
    ~Window();

    void setUpScaleFactor(const double upScaleBy);

    void mainLoop();
    bool isKeyPressed(const int &key) const;

    void add(Polygon &p);
    void add(Model &m);

    vector<Model> &getModels();
    SDL_Window *getWindow();
    SDL_Renderer *getRenderer();
    Renderer *getSpace();

protected:
    bool (*update)(Window *space);

    SDL_Window *wind;
    SDL_Renderer *rend;

    Renderer *space;

    set<int> keys;

    int delayTime;
};

#endif
