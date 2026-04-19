#include "joueur.h"
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <string.h>

#define LARGEUR_IMAGE 905
#define HAUTEUR_IMAGE 179
#define NBC 5
#define NBL 1

void init_j(joueur *j,SDL_Renderer *renderer){
j->sprite = IMG_LoadTexture(renderer, "sprite_p1.png");
 if (!j->sprite)
{
    printf("IMG error: %s\n", IMG_GetError());
}
else
{
    printf("Sprite chargé\n");
}
j->x=100;
j->y=300;
j->vitesse=5;
j->acceleration=2;


j->posscreen.x=(int)j->x;
j->posscreen.y=(int)j->y;
j->posscreen.w=140;
j->posscreen.h=140;


j->possprite.x=0;
j->possprite.y=0;
j->possprite.w=LARGEUR_IMAGE / NBC;
j->possprite.h=HAUTEUR_IMAGE / NBL;
j->direction=DROITE;

j->up=0;
j->score=0;
j->vies=3;
}  
void affich_j(joueur *j, SDL_Renderer *renderer)
{
   SDL_RenderCopy(
        renderer,j->sprite,&j->possprite,&j->posscreen  
    );
}
//void affich_j(joueur *j, SDL_Renderer *renderer)
//{
   // SDL_Rect dst = {100, 100, 200, 200};

    //if (SDL_RenderCopy(renderer, j->sprite, NULL, &dst) != 0)
    //{
      //  printf("RenderCopy error: %s\n", SDL_GetError());
    //}
    //}
void anim_j(joueur *j)
{
    j->possprite.y = 0;  // une seule ligne

    if (j->possprite.x >= (NBC -1 ) * j->possprite.w)
        j->possprite.x = 0;
    else
        j->possprite.x += j->possprite.w;
}
void dep_j(joueur *j, Uint32 dt)
{
    double dts = dt / 1000.0;
    double dx = 0.5 * j->acceleration * dts * dts
                + j->vitesse * dts;

    j->x += dx;
    j->vitesse += j->acceleration * dts;

  
    j->posscreen.x = (int)j->x;
}
void saut_j(joueur *j, int dt, int posinit)
{
    int seuil = posinit - 150;

    /* Phase de montée */
    if (j->up == 1)
    {
        if (j->posscreen.y > seuil)
            j->posscreen.y -= dt;
        else
            j->up = 2;
    }

    /* Phase de descente */
    if (j->up == 2)
    {
        if (j->posscreen.y < posinit)
            j->posscreen.y += dt;
        else
            j->up = 0; // fin du saut
    }
}
void liberer_j(joueur *j)
{
    if (j->sprite != NULL)
        SDL_DestroyTexture(j->sprite);
}
