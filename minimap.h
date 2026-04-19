#ifndef MINIMAP_H
#define MINIMAP_H

#include <SDL2/SDL.h>

typedef struct {
 SDL_Texture* backgroundTexture;
 SDL_Rect minimapPosition;

 SDL_Texture* playerTexture;
 SDL_Rect playerPosition;
} Minimap;

void MAJMinimap(SDL_Rect posJoueur, Minimap* m, SDL_Rect camera, int redim);
void afficher(SDL_Renderer* renderer, Minimap m);
void Liberer(Minimap* m);

#endif
