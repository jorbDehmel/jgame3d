/*
Jordan "Jorb" Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2022 - present
GPLv3 held by author
*/

#include "../text.hpp"

Writer::Writer(SDL_Renderer *Rend, const char *Path, const int Points)
{
    rend = Rend;
    surfaces.clear();

    TTF_Init();

    font = TTF_OpenFont(Path, Points);

    return;
}

Writer::~Writer()
{
    TTF_CloseFont(font);
    TTF_Quit();

    for (auto it = surfaces.begin(); it != surfaces.end(); it++)
    {
        if (it->second != nullptr)
        {
            SDL_DestroyTexture(it->second);
            surfaces[it->first] = nullptr;
        }
    }

    return;
}

void Writer::write(const string what, const double x, const double y, SDL_Color color)
{
    if (surfaces.count(what) == 0)
    {
        SDL_Surface *surf = TTF_RenderText_Solid(font, what.c_str(), color);
        surfaces[what] = SDL_CreateTextureFromSurface(rend, surf);
        SDL_FreeSurface(surf);
    }

    int w = 0, h = 0;
    SDL_QueryTexture(surfaces[what], NULL, NULL, &w, &h);

    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = w;
    dstRect.h = h;

    SDL_RenderCopy(rend, surfaces[what], NULL, &dstRect);

    return;
}
