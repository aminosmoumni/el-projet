#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "joueur.h"
int main(int argc,char *argv[]){
 SDL_Window *window=NULL;
 SDL_Renderer *renderer=NULL;
 SDL_Event event;
 
 int running=1;
 
 
 if(SDL_Init(SDL_INIT_VIDEO)!=0)
 {
  printf("erreur %s \n",SDL_GetError());
  return 1;
  }
  printf("photo existe");
 if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
{
    printf("Erreur IMG_Init: %s\n", IMG_GetError());
    return 1;
}
  
  window=SDL_CreateWindow("welcome to the game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_SHOWN);
  renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
  
  
  joueur j;
  init_j(&j,renderer);
  
  printf("photo existe");
  int posinit=j.posscreen.y;
  Uint32 lasttime=SDL_GetTicks();
  
  while(running){
   Uint32 currenttime =SDL_GetTicks();
   Uint32 dt=currenttime-lasttime;
   lasttime=currenttime; 
   while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;

            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        running = 0;
                        break;

                    case SDLK_RIGHT:
                        j.acceleration = 40;
                        j.direction = DROITE;
                        break;

                    case SDLK_LEFT:
                        j.acceleration = -40;
                        j.direction = GAUCHE;
                        break;

                    case SDLK_UP:
                        if (j.up == 0)
                            j.up = 1;
                        break;
                }
            }
            if (event.type == SDL_KEYUP)
            {
                if (event.key.keysym.sym == SDLK_RIGHT ||
                    event.key.keysym.sym == SDLK_LEFT)
                {
                    j.acceleration = 0;
                    j.vitesse = 0;
                }
            }
        }
        dep_j(&j ,dt);  
        saut_j(&j,dt,posinit);
        anim_j(&j);             

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        affich_j(&j, renderer);

        SDL_RenderPresent(renderer);
    }
    liberer_j(&j);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return 0;
}
