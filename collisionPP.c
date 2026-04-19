#include "collisionPP.h"

SDL_Color GetPixel(SDL_Surface *surface, int x, int y)
{
    SDL_Color color;
    Uint32 col;

    col = ((Uint32*)surface->pixels)[y * surface->w + x];

    SDL_GetRGB(col, surface->format, &color.r, &color.g, &color.b);

    return color;
}

int collisionPP(SDL_Surface *mask, int x, int y)
{
    SDL_Color c = GetPixel(mask, x, y);

    if(c.r == 0 && c.g == 0 && c.b == 0)
        return 1;

    return 0;
}
