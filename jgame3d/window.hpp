/*
Jordan "Jorb" Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2022 - present
GPLv3 held by author
*/

#ifndef WINDOW_H
#define WINDOW_H

#include "basics.hpp"
#include <set>

// Global representing the mouse's current position.
// Maintained by any Window instance.
extern SDL_Point mousePos;

// Global representing the mouse's current state.
// Maintained by any Window instance.
extern Uint32 mouseState;

// An easy-to-use overlay for an SDL2 window.
// Also handles keyboard and mouse events and maintains a steady framerate.
class Window
{
public:
    Window(int W, int H, int RefreshRate, bool (*Update)(Window *space),
           SDL_WindowFlags Flags = SDL_WINDOW_OPENGL);
    ~Window();

    // Set the upscale factor (so that the output is upScaleBy times larger)
    void setUpScaleFactor(const double upScaleBy);

    // Begin updating, rendering, and event tracking (until update returns false)
    void mainLoop();

    // Return if a key is currently pressed (see namespace keys::)
    bool isKeyPressed(const int &key) const;

    // Add a new polygon to the list of models to render
    void add(Polygon &p);

    // Add a new model to the list of models to render
    void add(Model &m);

    // Return all stored models (modifiable)
    vector<Model> &getModels();

    // Return the underlying SDL_Window instance (modifiable)
    SDL_Window *getWindow();

    // Return the underlying SDL_Renderer instance (modifiable)
    SDL_Renderer *getRenderer();

    // Return the Slicer instance (modifiable)
    Slicer *getSlicer();

    // The filter function, called once per frame after all other rendering
    void (*filter)(Window *wind) = nullptr;

protected:
    // The update function, called once per frame
    bool (*update)(Window *wind);

    // Underlying SDL2 window
    SDL_Window *wind;

    // Underlying SDL2 renderer
    SDL_Renderer *rend;

    // Slicer for rendering
    Slicer *space;

    // Set of all currently pressed keys
    set<int> keys;

    // Amount of time in milliseconds that a frame update
    // should take at minimum
    int delayTime;
};

#endif
