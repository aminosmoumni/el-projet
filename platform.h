#ifndef PLATFORM_H
#define PLATFORM_H

#include <SDL2/SDL.h>

typedef struct{
    SDL_Rect pos;
    int direction;
}Platform;

void updatePlatform(Platform* p);

#endif
