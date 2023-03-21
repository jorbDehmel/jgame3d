/*
Jordan "Jorb" Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2022 - present
GPLv3 held by author
*/

#ifndef TEXT_J
#define TEXT_J

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <map>
#include <string>
#include <iostream>
using namespace std;

// Compilation tag: -lSDL_ttf

// A user-friendly wrapper for the TTF_Font type
class Writer
{
public:
    Writer(SDL_Renderer *Rend, const char *Path, const int FontPoints);
    ~Writer();

    // Write text at a point in a color
    void write(const string what, const double x, const double y, SDL_Color color);

    // Pre-rendered phrases (stored in memory for efficiency)
    map<string, SDL_Texture *> surfaces;

protected:
    SDL_Renderer *rend;
    TTF_Font *font;
};

#endif
