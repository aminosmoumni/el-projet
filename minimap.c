#include "minimap.h"

void MAJMinimap(SDL_Rect posJoueur, Minimap* m, SDL_Rect camera, int redim)
{
    SDL_Rect posJoueurABS;

    // position réelle 
    posJoueurABS.x = posJoueur.x + camera.x;
    posJoueurABS.y = posJoueur.y + camera.y;

    // projection sur minimap
    m->playerPosition.x = m->minimapPosition.x + (posJoueurABS.x * redim) / 100;
    m->playerPosition.y = m->minimapPosition.y + (posJoueurABS.y * redim) / 100;

    m->playerPosition.w = 25;
    m->playerPosition.h = 25;
}
void afficher(SDL_Renderer* renderer, Minimap m)
{
 SDL_RenderCopy(renderer, m.backgroundTexture, NULL, &m.minimapPosition);
 SDL_RenderCopy(renderer, m.playerTexture, NULL, &m.playerPosition);
}
void Liberer(Minimap* m)
{
 if(m->backgroundTexture)
 {
  SDL_DestroyTexture(m->backgroundTexture);
  m->backgroundTexture = NULL;
 }

 if(m->playerTexture)
 {
  SDL_DestroyTexture(m->playerTexture);
  m->playerTexture = NULL;
 }
}
