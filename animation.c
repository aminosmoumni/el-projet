#include "animation.h"

void updateAnimation(Animation* a, int collision)
{
    if(collision)
    {
        a->timer++;

        if(a->timer % 10 == 0)
        {
            a->frame++;

            if(a->frame > 2)
                a->frame = 0;
        }
    }
}
void afficherAnimation(SDL_Renderer* r, Animation a)
{
    SDL_RenderCopy(r, a.tab[a.frame], NULL, &a.pos);
}
