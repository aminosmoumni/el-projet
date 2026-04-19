#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

#define MAX_BUTTONS 5
#define MAX_NAME 30

typedef struct
{
    SDL_Rect position;
    SDL_Texture *image;
    SDL_Texture *image_hover;
    int hovered;

}button;

typedef struct
{
    SDL_Rect position;
    SDL_Texture *image;

}background;

typedef struct
{
    SDL_Renderer *renderer;

    background bg;

    button btnCharger;
    button btnNouvellePartie;

    Mix_Music *music;
    Mix_Chunk *hover_sound;

    char playerName[MAX_NAME];

    int state;

}Menu;


void initMenu(Menu *menu, SDL_Renderer *renderer);

void loadMenu(Menu *menu);

void MenuEvent(Menu *menu, SDL_Event event);

void updateMenu(Menu *menu);

void renderMenu(Menu *menu);

void destroyMenu(Menu *menu);

void saveGame(char name[]);

void loadGame();

#endif
