#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string.h>
#include "menu.h"


/* ===================== */
/* INITIALISATION */
/* ===================== */

void initMenu(Menu *menu, SDL_Renderer *renderer)
{
    menu->renderer = renderer;
    menu->state = 0;

    strcpy(menu->playerName, "");

    loadMenu(menu);
}


/* ===================== */
/* CHARGEMENT */
/* ===================== */

void loadMenu(Menu *menu)
{
    SDL_Surface* surface;

    /* -------- BACKGROUND -------- */

    surface = IMG_Load("bgg.jpeg");

    menu->bg.image =
    SDL_CreateTextureFromSurface(menu->renderer, surface);

    SDL_FreeSurface(surface);

    menu->bg.position.x = 0;
    menu->bg.position.y = 0;
    menu->bg.position.w = 800;
    menu->bg.position.h = 600;



    /* -------- BOUTON CHARGER -------- */
    

    surface = IMG_Load("charger.png");

    menu->btnCharger.image =
    SDL_CreateTextureFromSurface(menu->renderer, surface);

    SDL_FreeSurface(surface);


    surface = IMG_Load("hover.png");

    menu->btnCharger.image_hover =
    SDL_CreateTextureFromSurface(menu->renderer, surface);

    SDL_FreeSurface(surface);


    menu->btnCharger.position.x = 300;
    menu->btnCharger.position.y = 200;
    menu->btnCharger.position.w = 550;
    menu->btnCharger.position.h = 200;

    menu->btnCharger.hovered = 0;



    /* -------- BOUTON NEW -------- */

    surface = IMG_Load("new.png");

    menu->btnNouvellePartie.image =
    SDL_CreateTextureFromSurface(menu->renderer, surface);

    SDL_FreeSurface(surface);


    surface = IMG_Load("new_hover.png");

    menu->btnNouvellePartie.image_hover =
    SDL_CreateTextureFromSurface(menu->renderer, surface);

    SDL_FreeSurface(surface);


    menu->btnNouvellePartie.position.x = 300;
    menu->btnNouvellePartie.position.y = 300;
    menu->btnNouvellePartie.position.w = 550;
    menu->btnNouvellePartie.position.h = 200;

    menu->btnNouvellePartie.hovered = 0;



    /* -------- SOUND -------- */

    menu->hover_sound = Mix_LoadWAV("hover.wav");

    menu->music = Mix_LoadMUS("music.mp3");

    Mix_PlayMusic(menu->music, -1);
}



/* ===================== */
/* EVENTS */
/* ===================== */

void MenuEvent(Menu *menu, SDL_Event event)
{
    int mouseX, mouseY;

    SDL_GetMouseState(&mouseX, &mouseY);


    /* BUTTON CHARGER */

    if(mouseX >= menu->btnCharger.position.x &&
       mouseX <= menu->btnCharger.position.x + menu->btnCharger.position.w &&
       mouseY >= menu->btnCharger.position.y &&
       mouseY <= menu->btnCharger.position.y + menu->btnCharger.position.h)
    {
        if(menu->btnCharger.hovered == 0)
        {
            menu->btnCharger.hovered = 1;

            Mix_PlayChannel(-1, menu->hover_sound, 0);
        }
    }
    else
    {
        menu->btnCharger.hovered = 0;
    }



    /* BUTTON NEW */

    if(mouseX >= menu->btnNouvellePartie.position.x &&
       mouseX <= menu->btnNouvellePartie.position.x + menu->btnNouvellePartie.position.w &&
       mouseY >= menu->btnNouvellePartie.position.y &&
       mouseY <= menu->btnNouvellePartie.position.y + menu->btnNouvellePartie.position.h)
    {
        if(menu->btnNouvellePartie.hovered == 0)
        {
            menu->btnNouvellePartie.hovered = 1;

            Mix_PlayChannel(-1, menu->hover_sound, 0);
        }
    }
    else
    {
        menu->btnNouvellePartie.hovered = 0;
    }



    if(event.type == SDL_MOUSEBUTTONDOWN)
    {

        if(menu->btnCharger.hovered)
        printf("Charger clique\n");


        if(menu->btnNouvellePartie.hovered)
        printf("Nouvelle partie clique\n ");

    }

}



/* ===================== */
/* RENDER */
/* ===================== */

void renderMenu(Menu *menu)
{

    SDL_RenderClear(menu->renderer);


    SDL_RenderCopy
    (
    menu->renderer,
    menu->bg.image,
    NULL,
    &menu->bg.position
    );



    if(menu->btnCharger.hovered)

    SDL_RenderCopy
    (
    menu->renderer,
    menu->btnCharger.image_hover,
    NULL,
    &menu->btnCharger.position
    );

    else

    SDL_RenderCopy
    (
    menu->renderer,
    menu->btnCharger.image,
    NULL,
    &menu->btnCharger.position
    );




    if(menu->btnNouvellePartie.hovered)

    SDL_RenderCopy
    (
    menu->renderer,
    menu->btnNouvellePartie.image_hover,
    NULL,
    &menu->btnNouvellePartie.position
    );

    else

    SDL_RenderCopy
    (
    menu->renderer,
    menu->btnNouvellePartie.image,
    NULL,
    &menu->btnNouvellePartie.position
    );



    SDL_RenderPresent(menu->renderer);

}



/* ===================== */
/* DESTROY */
/* ===================== */

void destroyMenu(Menu *menu)
{

SDL_DestroyTexture(menu->bg.image);


SDL_DestroyTexture(menu->btnCharger.image);

SDL_DestroyTexture(menu->btnCharger.image_hover);


SDL_DestroyTexture(menu->btnNouvellePartie.image);

SDL_DestroyTexture(menu->btnNouvellePartie.image_hover);


Mix_FreeChunk(menu->hover_sound);

Mix_FreeMusic(menu->music);

}
