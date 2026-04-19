#include "collisionBB.h"

int collisionBB(SDL_Rect A, SDL_Rect B)
{
    if (A.x + A.w < B.x) return 0;
    if (A.x > B.x + B.w) return 0;
    if (A.y + A.h < B.y) return 0;
    if (A.y > B.y + B.h) return 0;

    return 1;
}
