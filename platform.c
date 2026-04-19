#include "platform.h"

void updatePlatform(Platform* p)
{
    p->pos.x += 2 * p->direction;

    if(p->pos.x > 500)
        p->direction = -1;

    if(p->pos.x < 100)
        p->direction = 1;
}
