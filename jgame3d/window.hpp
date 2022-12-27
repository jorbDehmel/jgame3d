#ifndef WINDOW_H
#define WINDOW_H

#include "basics.hpp"
#include <set>

extern SDL_Point mousePos;
extern Uint32 mouseState;

class Window
{
public:
    Window(int W, int H, int RefreshRate, bool (*Update)(Window *space));
    ~Window();

    void mainLoop();
    bool isKeyPressed(const int &key) const;

    void add(Polygon &p);
    void add(Model &m);

    vector<Model> &getModels() const;
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
