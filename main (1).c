#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "enigme.h"

static SDL_Texture *renderText(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color)
{
    SDL_Surface *surface;
    SDL_Texture *texture;

    surface = TTF_RenderText_Blended(font, text, color);
    if (surface == NULL)
    {
        return NULL;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

static void afficherCoeurs(SDL_Renderer *renderer, SDL_Texture *coeur, int nb)
{
    int i;

    for (i = 0; i < nb; i++)
    {
        SDL_Rect pos = {50 + i * 70, 20, 60, 60};
        SDL_RenderCopy(renderer, coeur, NULL, &pos);
    }
}

static void afficherTimer(SDL_Renderer *renderer, int tempsRestant)
{
    SDL_Rect barre = {970, 25, 0, 28};
    float ratio;

    if (tempsRestant < 0)
    {
        tempsRestant = 0;
    }
    if (tempsRestant > 30)
    {
        tempsRestant = 30;
    }

    ratio = (float)tempsRestant / 30.0f;
    barre.w = (int)(210.0f * ratio);
    SDL_SetRenderDrawColor(renderer, 220, 40, 40, 255);
    SDL_RenderFillRect(renderer, &barre);
}

static void afficherFeedbackReponse(SDL_Renderer *renderer,
                                    TTF_Font *font,
                                    SDL_Texture *background,
                                    SDL_Texture *coeur,
                                    Enigme e,
                                    int vies,
                                    int tempsRestant,
                                    int choix,
                                    int estCorrecte)
{
    SDL_Color blanc = {255, 255, 255, 255};
    SDL_Color vert = {40, 220, 90, 255};
    SDL_Color rouge = {230, 60, 60, 255};
    SDL_Color couleurChoix = estCorrecte ? vert : rouge;
    SDL_Texture *tq;
    SDL_Texture *ta;
    SDL_Texture *tb;
    SDL_Texture *tc;
    SDL_Texture *message;
    SDL_Rect posQ = {100, 100, 0, 0};
    SDL_Rect posA = {190, 425, 0, 0};
    SDL_Rect posB = {540, 425, 0, 0};
    SDL_Rect posC = {890, 425, 0, 0};
    SDL_Rect posMessage = {0, 540, 0, 0};

    tq = renderText(renderer, font, e.question, blanc);
    ta = renderText(renderer, font, e.repA, choix == 1 ? couleurChoix : blanc);
    tb = renderText(renderer, font, e.repB, choix == 2 ? couleurChoix : blanc);
    tc = renderText(renderer, font, e.repC, choix == 3 ? couleurChoix : blanc);
    message = renderText(renderer, font, estCorrecte ? "Correct" : "Wrong", couleurChoix);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    afficherCoeurs(renderer, coeur, vies);
    afficherTimer(renderer, tempsRestant);

    if (tq != NULL)
    {
        SDL_QueryTexture(tq, NULL, NULL, &posQ.w, &posQ.h);
        SDL_RenderCopy(renderer, tq, NULL, &posQ);
    }
    if (ta != NULL)
    {
        SDL_QueryTexture(ta, NULL, NULL, &posA.w, &posA.h);
        SDL_RenderCopy(renderer, ta, NULL, &posA);
    }
    if (tb != NULL)
    {
        SDL_QueryTexture(tb, NULL, NULL, &posB.w, &posB.h);
        SDL_RenderCopy(renderer, tb, NULL, &posB);
    }
    if (tc != NULL)
    {
        SDL_QueryTexture(tc, NULL, NULL, &posC.w, &posC.h);
        SDL_RenderCopy(renderer, tc, NULL, &posC);
    }
    if (message != NULL)
    {
        SDL_QueryTexture(message, NULL, NULL, &posMessage.w, &posMessage.h);
        posMessage.x = (1280 - posMessage.w) / 2;
        SDL_RenderCopy(renderer, message, NULL, &posMessage);
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(1000);

    if (tq != NULL)
    {
        SDL_DestroyTexture(tq);
    }
    if (ta != NULL)
    {
        SDL_DestroyTexture(ta);
    }
    if (tb != NULL)
    {
        SDL_DestroyTexture(tb);
    }
    if (tc != NULL)
    {
        SDL_DestroyTexture(tc);
    }
    if (message != NULL)
    {
        SDL_DestroyTexture(message);
    }
}

static void afficherFin(SDL_Renderer *renderer, TTF_Font *font, const char *texte, SDL_Color color)
{
    SDL_Texture *textureTitre;
    SDL_Texture *textureSousTexte;
    SDL_Rect posTitre = {0, 0, 0, 0};
    SDL_Rect posSousTexte = {0, 0, 0, 0};
    SDL_Rect panneau = {300, 180, 680, 280};
    SDL_Color fond;
    SDL_Color blanc = {255, 255, 255, 255};
    const char *sousTexte;
    SDL_Event ev;
    int running = 1;

    if (strcmp(texte, "YOU WIN") == 0)
    {
        fond = (SDL_Color){18, 90, 50, 255};
        sousTexte = "Bonne reponse";
    }
    else
    {
        fond = (SDL_Color){120, 32, 32, 255};
        sousTexte = "Mauvaise reponse";
    }

    textureTitre = renderText(renderer, font, texte, color);
    textureSousTexte = renderText(renderer, font, sousTexte, blanc);
    if (textureTitre == NULL || textureSousTexte == NULL)
    {
        if (textureTitre != NULL)
        {
            SDL_DestroyTexture(textureTitre);
        }
        if (textureSousTexte != NULL)
        {
            SDL_DestroyTexture(textureSousTexte);
        }
        return;
    }

    SDL_QueryTexture(textureTitre, NULL, NULL, &posTitre.w, &posTitre.h);
    SDL_QueryTexture(textureSousTexte, NULL, NULL, &posSousTexte.w, &posSousTexte.h);
    posTitre.x = (1280 - posTitre.w) / 2;
    posTitre.y = 270;
    posSousTexte.x = (1280 - posSousTexte.w) / 2;
    posSousTexte.y = 340;

    while (running)
    {
        SDL_SetRenderDrawColor(renderer, fond.r, fond.g, fond.b, fond.a);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 220);
        SDL_RenderFillRect(renderer, &panneau);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &panneau);

        SDL_RenderCopy(renderer, textureTitre, NULL, &posTitre);
        SDL_RenderCopy(renderer, textureSousTexte, NULL, &posSousTexte);
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_QUIT)
            {
                running = 0;
            }
            else if (ev.type == SDL_MOUSEBUTTONDOWN)
            {
                running = 0;
            }
            else if (ev.type == SDL_KEYDOWN)
            {
                if (ev.key.keysym.sym == SDLK_RETURN || ev.key.keysym.sym == SDLK_ESCAPE)
                {
                    running = 0;
                }
            }
        }

        SDL_Delay(16);
    }

    SDL_DestroyTexture(textureTitre);
    SDL_DestroyTexture(textureSousTexte);
}

static int pointDansRect(int x, int y, SDL_Rect r)
{
    return x >= r.x && x <= r.x + r.w &&
           y >= r.y && y <= r.y + r.h;
}

int main(void)
{
    SDL_Window *win;
    SDL_Renderer *renderer;
    TTF_Font *font;
    SDL_Color white = {255, 255, 255, 255};
    SDL_Texture *background;
    SDL_Texture *coeur;
    Enigme Q[MAX_QUESTIONS];
    int nbQ;
    int vies = 3;
    int bonnesReponses = 0;
    int id;
    Enigme e;
    SDL_Event ev;
    int running = 1;
    int resultat = 0;
    Uint32 debutTemps;

    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        return 1;
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0)
    {
        SDL_Quit();
        return 1;
    }

    if (TTF_Init() != 0)
    {
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    win = SDL_CreateWindow("Enigmes",
                           SDL_WINDOWPOS_CENTERED,
                           SDL_WINDOWPOS_CENTERED,
                           1280,
                           720,
                           0);
    if (win == NULL)
    {
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(win, -1, 0);
    if (renderer == NULL)
    {
        SDL_DestroyWindow(win);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    font = TTF_OpenFont("arial.ttf", 32);
    if (font == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    background = IMG_LoadTexture(renderer, "background.png");
    coeur = IMG_LoadTexture(renderer, "coeur.png");
    if (background == NULL || coeur == NULL)
    {
        if (background != NULL)
        {
            SDL_DestroyTexture(background);
        }
        if (coeur != NULL)
        {
            SDL_DestroyTexture(coeur);
        }

        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    nbQ = chargerEnigmes(Q, "questions.txt");
    if (nbQ <= 0)
    {
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(coeur);
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    srand((unsigned int)time(NULL));
    id = tirerQuestion(Q, nbQ);
    e = Q[id];
    debutTemps = SDL_GetTicks();

    while (running && vies > 0)
    {
        SDL_Texture *tq;
        SDL_Texture *ta;
        SDL_Texture *tb;
        SDL_Texture *tc;
        SDL_Rect posQ = {100, 100, 0, 0};
        SDL_Rect posA = {190, 425, 0, 0};
        SDL_Rect posB = {540, 425, 0, 0};
        SDL_Rect posC = {890, 425, 0, 0};
        SDL_Rect zoneA;
        SDL_Rect zoneB;
        SDL_Rect zoneC;
        int tempsEcoule = (int)((SDL_GetTicks() - debutTemps) / 1000);
        int tempsRestant = 30 - tempsEcoule;

        if (tempsRestant <= 0)
        {
            running = 0;
            resultat = -1;
            tempsRestant = 0;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, background, NULL, NULL);
        afficherCoeurs(renderer, coeur, vies);
        afficherTimer(renderer, tempsRestant);

        tq = renderText(renderer, font, e.question, white);
        ta = renderText(renderer, font, e.repA, white);
        tb = renderText(renderer, font, e.repB, white);
        tc = renderText(renderer, font, e.repC, white);

        if (tq != NULL)
        {
            SDL_QueryTexture(tq, NULL, NULL, &posQ.w, &posQ.h);
            SDL_RenderCopy(renderer, tq, NULL, &posQ);
        }

        if (ta != NULL)
        {
            SDL_QueryTexture(ta, NULL, NULL, &posA.w, &posA.h);
            SDL_RenderCopy(renderer, ta, NULL, &posA);
        }

        if (tb != NULL)
        {
            SDL_QueryTexture(tb, NULL, NULL, &posB.w, &posB.h);
            SDL_RenderCopy(renderer, tb, NULL, &posB);
        }

        if (tc != NULL)
        {
            SDL_QueryTexture(tc, NULL, NULL, &posC.w, &posC.h);
            SDL_RenderCopy(renderer, tc, NULL, &posC);
        }

        zoneA.x = posA.x - 20;
        zoneA.y = posA.y - 10;
        zoneA.w = posA.w + 40;
        zoneA.h = posA.h + 20;

        zoneB.x = posB.x - 20;
        zoneB.y = posB.y - 10;
        zoneB.w = posB.w + 40;
        zoneB.h = posB.h + 20;

        zoneC.x = posC.x - 20;
        zoneC.y = posC.y - 10;
        zoneC.w = posC.w + 40;
        zoneC.h = posC.h + 20;

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_QUIT)
            {
                running = 0;
            }

            if (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT)
            {
                int x = ev.button.x;
                int y = ev.button.y;
                int ch = 0;

                if (pointDansRect(x, y, zoneA))
                {
                    ch = 1;
                }
                else if (pointDansRect(x, y, zoneB))
                {
                    ch = 2;
                }
                else if (pointDansRect(x, y, zoneC))
                {
                    ch = 3;
                }

                if (ch != 0)
                {
                    if (ch == e.bonneReponse)
                    {
                        afficherFeedbackReponse(renderer, font, background, coeur, e, vies, tempsRestant, ch, 1);
                        bonnesReponses++;
                        if (bonnesReponses >= 3)
                        {
                            resultat = 1;
                            running = 0;
                        }
                    }
                    else
                    {
                        vies--;
                        afficherFeedbackReponse(renderer, font, background, coeur, e, vies, tempsRestant, ch, 0);
                        if (vies <= 0)
                        {
                            resultat = -1;
                            running = 0;
                        }
                    }

                    if (running && vies > 0)
                    {
                        id = tirerQuestion(Q, nbQ);
                        e = Q[id];
                    }
                }
            }
        }

        if (tq != NULL)
        {
            SDL_DestroyTexture(tq);
        }
        if (ta != NULL)
        {
            SDL_DestroyTexture(ta);
        }
        if (tb != NULL)
        {
            SDL_DestroyTexture(tb);
        }
        if (tc != NULL)
        {
            SDL_DestroyTexture(tc);
        }
    }

    if (resultat == 1)
    {
        afficherFin(renderer, font, "YOU WIN", white);
    }
    else
    {
        afficherFin(renderer, font, "YOU LOSE", white);
    }

    SDL_DestroyTexture(background);
    SDL_DestroyTexture(coeur);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}
