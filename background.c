#include "background.h"
#include <stdio.h>
#include <stdlib.h>

void initBackground(Background *bg, SDL_Renderer *renderer)
{
    SDL_Surface *surface = IMG_Load("jungle01.png");

    if (!surface)
    {
        printf("❌ IMG_Load error: %s\n", IMG_GetError());
        exit(1);
    }

    bg->image = SDL_CreateTextureFromSurface(renderer, surface);

    if (!bg->image)
    {
        printf("❌ Texture error: %s\n", SDL_GetError());
        exit(1);
    }

    bg->width = surface->w;
    bg->height = surface->h;

    printf("✅ Background loaded: %dx%d\n", bg->width, bg->height);

    SDL_FreeSurface(surface);

   
    bg->camera.x = 0;
    bg->camera.y = 0;
    int screenW = 800;
    int screenH = 600;

    bg->camera.x = 0;
    bg->camera.y = 0;
    bg->camera.w = screenW;
    bg->camera.h = screenH;
}

void afficherBackground(Background *bg, SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, bg->image, &bg->camera, NULL);
}

void scrolling(Background *bg, int direction, int pas)
{
    if (direction == 0) 
    {
        bg->camera.x += pas;
        if (bg->camera.x + bg->camera.w > bg->width)
            bg->camera.x = bg->width - bg->camera.w;
    }
    else if (direction == 1) 
    {
        bg->camera.x -= pas;
        if (bg->camera.x < 0)
            bg->camera.x = 0;
    }
}

void freeBackground(Background *bg)
{
    SDL_DestroyTexture(bg->image);
}
