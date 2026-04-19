#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "minimap.h"
#include "collisionPP.h"
#include "collisionBB.h"
#include "platform.h"
#include "animation.h"

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* w = SDL_CreateWindow("MINIMAP",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,600,0);

    SDL_Renderer* r = SDL_CreateRenderer(w,-1,0);

    /* ===== PLAYER ===== */
    SDL_Rect player = {100,100,50,50};
    SDL_Texture* playerTex = IMG_LoadTexture(r,"player_minimap.png");

    /* ===== CAMERA ===== */
    SDL_Rect camera = {0,0,800,600};

    /* ===== MINIMAP ===== */
    Minimap m;
    m.backgroundTexture = IMG_LoadTexture(r,"background_minimap.png");
    m.playerTexture = IMG_LoadTexture(r,"player_minimap.png");
    m.minimapPosition = (SDL_Rect){600,20,150,100};

    int redim = 20;

    /* ===== MASK ===== */
    SDL_Surface* mask = IMG_Load("backgroundMasque.png");

    /* ===== PLATFORM ===== */
    Platform p;
    p.pos = (SDL_Rect){200,300,120,20};
    p.direction = 1;

    /* ===== ANIMATION ===== */
    Animation a;
    a.frame = 0;
    a.timer = 0; 
    a.pos = (SDL_Rect){0,0,800,600};

    a.tab[0] = IMG_LoadTexture(r,"bg1.png");
    a.tab[1] = IMG_LoadTexture(r,"bg2.png");
    a.tab[2] = IMG_LoadTexture(r,"bg3.png");

    int run = 1;
    SDL_Event e;

    while(run)
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
                run = 0;
        }

        /* ===== CLAVIER ===== */
        const Uint8* k = SDL_GetKeyboardState(NULL);

        if(k[SDL_SCANCODE_RIGHT]) player.x += 3;
        if(k[SDL_SCANCODE_LEFT])  player.x -= 3;
        if(k[SDL_SCANCODE_UP])    player.y -= 3;
        if(k[SDL_SCANCODE_DOWN])  player.y += 3;

        /* ===== UPDATE PLATFORM ===== */
        updatePlatform(&p);

        /* ===== COLLISION BB ===== */
        int collBB = collisionBB(player,p.pos);
        if(collBB)
            player.y = p.pos.y - player.h;

        /* ===== COLLISION PIXEL ===== */
        int collPP = collisionPP(mask, player.x + player.w/2, player.y + player.h);

        /* ===== ANIMATION ===== */
        updateAnimation(&a, collBB || collPP);

        /* ===== MINIMAP ===== */
        MAJMinimap(player,&m,camera,redim);

        /* ===== RENDER ===== */
        SDL_RenderClear(r);

        afficherAnimation(r,a);

        SDL_SetRenderDrawColor(r,255,0,0,255);
        SDL_RenderFillRect(r,&p.pos);

        SDL_RenderCopy(r, playerTex, NULL, &player);

        afficher(r,m);

        SDL_RenderPresent(r);
    }

    /* ===== FREE ===== */
    SDL_FreeSurface(mask);
    Liberer(&m);

    SDL_DestroyTexture(playerTex);
    SDL_DestroyTexture(a.tab[0]);
    SDL_DestroyTexture(a.tab[1]);
    SDL_DestroyTexture(a.tab[2]);

    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);

    IMG_Quit();
    SDL_Quit();

    return 0;
}
