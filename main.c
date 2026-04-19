#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include "menu.h"

int main(int argc, char* argv[])
{

SDL_Window* window=NULL;

SDL_Renderer* renderer=NULL;

SDL_Event event;

int running=1;



/* INIT SDL */

SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);

IMG_Init(IMG_INIT_PNG);

Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);



/* WINDOW */

window=
SDL_CreateWindow
(
"jumangi Game Menu",

SDL_WINDOWPOS_CENTERED,

SDL_WINDOWPOS_CENTERED,

800,

600,

0
);



renderer=
SDL_CreateRenderer
(
window,

-1,

SDL_RENDERER_ACCELERATED
);



/* MENU */

Menu menu;

initMenu(&menu,renderer);



/* BOUCLE PRINCIPALE */

while(running)
{


while(SDL_PollEvent(&event))
{

if(event.type==SDL_QUIT)

running=0;



MenuEvent(&menu,event);

}



renderMenu(&menu);



SDL_Delay(16); //fps(60)

}



/* DESTROY */

destroyMenu(&menu);

SDL_DestroyRenderer(renderer);

SDL_DestroyWindow(window);

Mix_CloseAudio();

IMG_Quit();

SDL_Quit();

return 0;

}
