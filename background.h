#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct
{
    SDL_Texture *image;
    SDL_Rect camera;
    int width;
    int height;
} Background;

void initBackground(Background *bg, SDL_Renderer *renderer);
void afficherBackground(Background *bg, SDL_Renderer *renderer);
void scrolling(Background *bg, int direction, int pas);
void freeBackground(Background *bg);

#endif
