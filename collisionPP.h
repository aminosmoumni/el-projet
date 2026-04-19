#ifndef COLLISIONPP_H
#define COLLISIONPP_H

#include <SDL2/SDL.h>

SDL_Color GetPixel(SDL_Surface *surface, int x, int y);
int collisionPP(SDL_Surface *mask, int x, int y);

#endif
