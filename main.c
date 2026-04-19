#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "ennemi.h"

void afficherVieJoueur(SDL_Renderer *renderer, int vie, int vieMax)
{
    SDL_Rect fond;
    fond.x = 10;
    fond.y = 10;
    fond.w = 200;
    fond.h = 16;

    SDL_Rect barre;
    barre.x = 10;
    barre.y = 10;
    barre.w = (vie * 200) / vieMax;
    barre.h = 16;

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderFillRect(renderer, &fond);

    if (vie > 60)
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    else if (vie > 30)
        SDL_SetRenderDrawColor(renderer, 255, 140, 0, 255);
    else
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_RenderFillRect(renderer, &barre);
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window *window = SDL_CreateWindow(
        "Test Ennemi",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        0
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // ======================
    // Joueur
    // ======================
    SDL_Rect joueur;
    joueur.x = 100;
    joueur.y = 100;
    joueur.w = 40;
    joueur.h = 40;

    int vieJoueur      = 100;
    int vieMaxJoueur   = 100;
    int cooldownJoueur = 0;

    // ======================
    // Ennemi
    // ======================
    Ennemi e;
    initEnnemi(&e, renderer, "guard.png", 300, 200, 96, 96);

    int running = 1;
    SDL_Event event;

    while (running)
    {
        // EVENTS
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;

            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_RIGHT: joueur.x += 10; break;
                    case SDLK_LEFT:  joueur.x -= 10; break;
                    case SDLK_UP:    joueur.y -= 10; break;
                    case SDLK_DOWN:  joueur.y += 10; break;

                    // ESPACE = joueur attaque l'ennemi
                    case SDLK_SPACE:
                        if (collisionEnnemi(joueur, &e) && e.cooldownBlessure == 0)
                        {
                            blesserEnnemi(&e, 10);
                            e.cooldownBlessure = 60;
                        }
                        break;
                }
            }
        }

        // UPDATE
        deplacerEnnemi(&e);

        if (e.cooldownBlessure > 0)
            e.cooldownBlessure--;

        if (cooldownJoueur > 0)
            cooldownJoueur--;

        // Ennemi attaque joueur par contact
        if (collisionEnnemi(joueur, &e) && cooldownJoueur == 0)
        {
            vieJoueur -= e.degat;
            cooldownJoueur = 60;

            if (vieJoueur <= 0)
            {
                vieJoueur = 0;
                printf("Joueur mort !\n");
                running = 0;
            }
        }

        // RENDER
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Joueur (bleu)
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &joueur);

        // Ennemi
        afficherEnnemi(&e, renderer);
        afficherVieEnnemi(&e, renderer);

        // Vie joueur
        afficherVieJoueur(renderer, vieJoueur, vieMaxJoueur);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    // CLEAN
    libererEnnemi(&e);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
