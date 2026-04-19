#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "background.h"

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        printf("IMG init error: %s\n", IMG_GetError());
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("Scrolling Game",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600,
                                          0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    
    Background bg;
    initBackground(&bg, renderer);

    
    SDL_Surface *pSurf = IMG_Load("player.png");
    if (!pSurf)
    {
        printf(" Player load error: %s\n", IMG_GetError());
        return -1;
    }

    SDL_Texture *player = SDL_CreateTextureFromSurface(renderer, pSurf);
    SDL_FreeSurface(pSurf);

    if (!player)
    {
        printf(" Player texture error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Rect posPlayer = {350, 400, 80, 80};

    int running = 1;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;
        }

        const Uint8 *keystate = SDL_GetKeyboardState(NULL);

        
        if (keystate[SDL_SCANCODE_RIGHT])
        {
            posPlayer.x += 5;

        if (posPlayer.x >= 400)
        {
            posPlayer.x = 400;
            scrolling(&bg, 0, 5);
        }
    }

if (keystate[SDL_SCANCODE_LEFT])
{
    posPlayer.x -= 5;

    if (posPlayer.x <= 200)
    {
        posPlayer.x = 200;
        scrolling(&bg, 1, 5);
    }
}

        SDL_RenderClear(renderer);

        afficherBackground(&bg, renderer);
        SDL_RenderCopy(renderer, player, NULL, &posPlayer);

        SDL_RenderPresent(renderer);
    }

    
    SDL_DestroyTexture(player);
    freeBackground(&bg);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return 0;
}
