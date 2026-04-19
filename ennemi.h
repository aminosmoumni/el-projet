#ifndef ENNEMI_H
#define ENNEMI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct
{
    SDL_Texture *texture;
    SDL_Rect pos;
    SDL_Rect posSprite;
    SDL_Rect hitbox;
    int direction;
    int vitesse;
    int xMin, xMax;
    int yMin, yMax;
    int vie;
    int vieMax;
    int etat;
    int degat;
    int modeDeplacement;
    int frame;
    int nbFrames;
    int timerFrame;
    int delayFrame;
    int cooldownBlessure;
    int frameW;
    int frameH;
} Ennemi;

void initEnnemi(Ennemi *e, SDL_Renderer *renderer, const char *path, int x, int y, int w, int h);
void deplacerEnnemi(Ennemi *e);
void afficherEnnemi(Ennemi *e, SDL_Renderer *renderer);
void majHitboxEnnemi(Ennemi *e);
int  collisionEnnemi(SDL_Rect joueur, Ennemi *e);
int  hitJoueurParEnnemi(SDL_Rect joueur, Ennemi *e);
void blesserEnnemi(Ennemi *e, int degat);
void afficherVieEnnemi(Ennemi *e, SDL_Renderer *renderer);
void libererEnnemi(Ennemi *e);

#endif
