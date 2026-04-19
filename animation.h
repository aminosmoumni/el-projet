#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL.h>

typedef struct{
    SDL_Texture* tab[3];
    int frame;
    int timer;
    SDL_Rect pos;
}Animation;

void updateAnimation(Animation* a, int collision);
void afficherAnimation(SDL_Renderer* r, Animation a);

#endif
