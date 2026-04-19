#ifndef JOUEUR_H
#define JOUEUR_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#define DROITE 0
#define GAUCHE 1
typedef struct{
 SDL_Texture *sprite;
 SDL_Rect possprite;
 SDL_Rect posscreen;
 int direction;
 double x,y;
 double vitesse;
 double acceleration;
 int up;
 int score;
 int vies;
 }joueur;
 
 
 void init_j(joueur *j,SDL_Renderer *renderer);
 void affich_j(joueur *j,SDL_Renderer *renderer);
 void anim_j(joueur *j);
 void dep_j(joueur *j, Uint32 dt);
 void saut_j(joueur *j, int dt, int posinit);
 void liberer_j(joueur *j);
 
 
 
 #endif



