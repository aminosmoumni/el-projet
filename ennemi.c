#include "ennemi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void majHitboxEnnemi(Ennemi *e)
{
    e->hitbox.x = e->pos.x + e->pos.w / 4;
    e->hitbox.y = e->pos.y + e->pos.h / 4;
    e->hitbox.w = e->pos.w / 2;
    e->hitbox.h = e->pos.h / 2;
}

void initEnnemi(Ennemi *e, SDL_Renderer *renderer, const char *path, int x, int y, int w, int h)
{
    e->texture = IMG_LoadTexture(renderer, path);

    if (e->texture == NULL)
    {
        printf("Erreur chargement sprite ennemi : %s\n", IMG_GetError());
        e->frameW = 64;
        e->frameH = 64;
    }
    else
    {
        int texW = 0, texH = 0;
        SDL_QueryTexture(e->texture, NULL, NULL, &texW, &texH);
        printf("Sprite sheet : %d x %d pixels\n", texW, texH);

        // 4 colonnes x 2 lignes
        e->frameW = texW / 4;
        e->frameH = texH / 2;
        printf("Frame size : %d x %d\n", e->frameW, e->frameH);
    }

    e->pos.x = x;
    e->pos.y = y;
    e->pos.w = w;
    e->pos.h = h;

    e->posSprite.x = 0;
    e->posSprite.y = 0;
    e->posSprite.w = e->frameW;
    e->posSprite.h = e->frameH;

    e->direction       = 1;
    e->vitesse         = 2;

    e->xMin = x - 150;
    e->xMax = x + 150;
    e->yMin = y - 100;
    e->yMax = y + 100;

    e->vieMax = 100;
    e->vie    = 100;
    e->etat   = 1; // 1=marche, 2=blessé, 3=mort

    e->degat           = 10;
    e->modeDeplacement = 1;

    e->frame      = 0;
    e->nbFrames   = 4;
    e->timerFrame = 0;
    e->delayFrame = 8;

    e->cooldownBlessure = 0;

    majHitboxEnnemi(e);
    srand(time(NULL));
}

void deplacerEnnemi(Ennemi *e)
{
    if (e->etat == 3)
        return;

    // Si etat == 2 (blessé) : jouer animation attaque ligne 1, ne pas bouger
    if (e->etat == 2)
    {
        e->posSprite.y = e->frameH; // ligne 2 = attaque
        e->nbFrames    = 3;

        e->timerFrame++;
        if (e->timerFrame >= e->delayFrame)
        {
            e->timerFrame = 0;
            e->frame++;
            if (e->frame >= e->nbFrames)
            {
                e->frame    = 0;
                e->etat     = 1;      // retour à marche après animation
                e->nbFrames = 4;
            }
        }

        e->posSprite.x = e->frame * e->frameW;
        e->posSprite.w = e->frameW;
        e->posSprite.h = e->frameH;
        majHitboxEnnemi(e);
        return; // ne pas bouger pendant l'animation
    }

    // etat == 1 : marche normale (ligne 0)
    e->posSprite.y = 0;

    if (e->modeDeplacement == 1)
    {
        if (e->direction == 1)
        {
            e->pos.x += e->vitesse;
            if (e->pos.x >= e->xMax)
            {
                e->direction = -1;
                if (rand() % 2 == 0)
                    e->modeDeplacement = 2;
            }
        }
        else
        {
            e->pos.x -= e->vitesse;
            if (e->pos.x <= e->xMin)
            {
                e->direction = 1;
                if (rand() % 2 == 0)
                    e->modeDeplacement = 2;
            }
        }
    }
    else if (e->modeDeplacement == 2)
    {
        if (e->direction == 1)
        {
            e->pos.y += e->vitesse;
            if (e->pos.y >= e->yMax)
            {
                e->direction = -1;
                if (rand() % 2 == 0)
                    e->modeDeplacement = 1;
            }
        }
        else
        {
            e->pos.y -= e->vitesse;
            if (e->pos.y <= e->yMin)
            {
                e->direction = 1;
                if (rand() % 2 == 0)
                    e->modeDeplacement = 1;
            }
        }
    }

    // Animation marche
    e->timerFrame++;
    if (e->timerFrame >= e->delayFrame)
    {
        e->timerFrame = 0;
        e->frame++;
        if (e->frame >= e->nbFrames)
            e->frame = 0;
    }

    e->posSprite.x = e->frame * e->frameW;
    e->posSprite.w = e->frameW;
    e->posSprite.h = e->frameH;

    majHitboxEnnemi(e);
}

void afficherEnnemi(Ennemi *e, SDL_Renderer *renderer)
{
    if (e->etat != 3 && e->texture != NULL)
        SDL_RenderCopy(renderer, e->texture, &e->posSprite, &e->pos);
}

int collisionEnnemi(SDL_Rect joueur, Ennemi *e)
{
    if (e->etat == 3)
        return 0;
    return SDL_HasIntersection(&joueur, &e->hitbox);
}

int hitJoueurParEnnemi(SDL_Rect joueur, Ennemi *e)
{
    if (collisionEnnemi(joueur, e))
        return e->degat;
    return 0;
}

void blesserEnnemi(Ennemi *e, int degat)
{
    if (e->etat == 3)
        return;

    e->vie -= degat;

    if (e->vie <= 0)
    {
        e->vie  = 0;
        e->etat = 3;
        printf("Ennemi mort !\n");
    }
    else
    {
        // Déclenche animation attaque (ligne 2)
        e->etat        = 2;
        e->frame       = 0;
        e->timerFrame  = 0;
        e->nbFrames    = 3;
        e->posSprite.y = e->frameH;
    }
}

void afficherVieEnnemi(Ennemi *e, SDL_Renderer *renderer)
{
    SDL_Rect fond;
    fond.x = e->pos.x;
    fond.y = e->pos.y - 10;
    fond.w = e->pos.w;
    fond.h = 6;

    SDL_Rect vie;
    vie.x = e->pos.x;
    vie.y = e->pos.y - 10;
    vie.w = (e->vie * e->pos.w) / e->vieMax;
    vie.h = 6;

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderFillRect(renderer, &fond);

    if (e->vie > 60)
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    else if (e->vie > 30)
        SDL_SetRenderDrawColor(renderer, 255, 140, 0, 255);
    else
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_RenderFillRect(renderer, &vie);
}

void libererEnnemi(Ennemi *e)
{
    if (e->texture != NULL)
    {
        SDL_DestroyTexture(e->texture);
        e->texture = NULL;
    }
}
