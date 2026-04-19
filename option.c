#include "option.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

void menuOption(SDL_Window *window,
                SDL_Renderer *renderer)
{

SDL_Event event;
int running=1;

/* Background */
SDL_Texture *bg =
IMG_LoadTexture(renderer,"bg2.jpg");

SDL_Rect posBg={0,0,800,600};

/* Music */
Mix_Music *music =
Mix_LoadMUS("music2.mp3");

Mix_PlayMusic(music,-1);

int volume=64;
Mix_VolumeMusic(volume);

/* Boutons positions */
SDL_Rect diminuer={200,200,200,60};
SDL_Rect augmenter={450,200,200,60};
SDL_Rect normal={200,300,200,60};
SDL_Rect plein={450,300,200,60};
SDL_Rect retour={325,420,200,60};

/* Charger images boutons */
SDL_Texture *btnDim =
IMG_LoadTexture(renderer,"btn_dim.png");

SDL_Texture *btnAug =
IMG_LoadTexture(renderer,"btn_aug.png");

SDL_Texture *btnNormal =
IMG_LoadTexture(renderer,"btn_normal.png");

SDL_Texture *btnFull =
IMG_LoadTexture(renderer,"btn_full.png");

SDL_Texture *btnRetour =
IMG_LoadTexture(renderer,"btn_retour.png");

/* Texte */
TTF_Font *font =
TTF_OpenFont("arial.ttf",24);

SDL_Color blanc={255,255,255,255};

SDL_Surface *sDim =
TTF_RenderText_Solid(font,"DIMINUER",blanc);
SDL_Texture *tDim =
SDL_CreateTextureFromSurface(renderer,sDim);

SDL_Surface *sAug =
TTF_RenderText_Solid(font,"AUGMENTER",blanc);
SDL_Texture *tAug =
SDL_CreateTextureFromSurface(renderer,sAug);

SDL_Surface *sNormal =
TTF_RenderText_Solid(font,"NORMAL",blanc);
SDL_Texture *tNormal =
SDL_CreateTextureFromSurface(renderer,sNormal);

SDL_Surface *sFull =
TTF_RenderText_Solid(font,"PLEIN D'ECRAN",blanc);
SDL_Texture *tFull =
SDL_CreateTextureFromSurface(renderer,sFull);

SDL_Surface *sRetour =
TTF_RenderText_Solid(font,"RETOUR",blanc);
SDL_Texture *tRetour =
SDL_CreateTextureFromSurface(renderer,sRetour);

while(running)
{

while(SDL_PollEvent(&event))
{

if(event.type==SDL_QUIT)
running=0;

if(event.type==SDL_KEYDOWN)
{
if(event.key.keysym.sym==SDLK_PLUS)
{
volume+=10;
if(volume>128) volume=128;
Mix_VolumeMusic(volume);
}

if(event.key.keysym.sym==SDLK_MINUS)
{
volume-=10;
if(volume<0) volume=0;
Mix_VolumeMusic(volume);
}
}

if(event.type==SDL_MOUSEBUTTONDOWN)
{

int x=event.button.x;
int y=event.button.y;

if(x>diminuer.x && x<diminuer.x+diminuer.w &&
   y>diminuer.y && y<diminuer.y+diminuer.h)
{
volume-=10;
if(volume<0) volume=0;
Mix_VolumeMusic(volume);
}

if(x>augmenter.x && x<augmenter.x+augmenter.w &&
   y>augmenter.y && y<augmenter.y+augmenter.h)
{
volume+=10;
if(volume>128) volume=128;
Mix_VolumeMusic(volume);
}

if(x>plein.x && x<plein.x+plein.w &&
   y>plein.y && y<plein.y+plein.h)
{
SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);
}

if(x>normal.x && x<normal.x+normal.w &&
   y>normal.y && y<normal.y+normal.h)
{
SDL_SetWindowFullscreen(window,0);
}

if(x>retour.x && x<retour.x+retour.w &&
   y>retour.y && y<retour.y+retour.h)
{
running=0;
}

}

}

/* Affichage */

SDL_RenderClear(renderer);

SDL_RenderCopy(renderer,bg,NULL,&posBg);

SDL_RenderCopy(renderer,btnDim,NULL,&diminuer);
SDL_RenderCopy(renderer,btnAug,NULL,&augmenter);
SDL_RenderCopy(renderer,btnNormal,NULL,&normal);
SDL_RenderCopy(renderer,btnFull,NULL,&plein);
SDL_RenderCopy(renderer,btnRetour,NULL,&retour);

/* Text au centre des boutons */
SDL_RenderCopy(renderer,tDim,NULL,&diminuer);
SDL_RenderCopy(renderer,tAug,NULL,&augmenter);
SDL_RenderCopy(renderer,tNormal,NULL,&normal);
SDL_RenderCopy(renderer,tFull,NULL,&plein);
SDL_RenderCopy(renderer,tRetour,NULL,&retour);

SDL_RenderPresent(renderer);

}

/* Liberation */

SDL_DestroyTexture(bg);

SDL_DestroyTexture(btnDim);
SDL_DestroyTexture(btnAug);
SDL_DestroyTexture(btnNormal);
SDL_DestroyTexture(btnFull);
SDL_DestroyTexture(btnRetour);

SDL_DestroyTexture(tDim);
SDL_DestroyTexture(tAug);
SDL_DestroyTexture(tNormal);
SDL_DestroyTexture(tFull);
SDL_DestroyTexture(tRetour);

TTF_CloseFont(font);
Mix_FreeMusic(music);

}
