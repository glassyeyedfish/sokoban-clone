#include "components.h"

int
aabb_is_overlapping(aabb_t* a, aabb_t* b) {

        return a->x <= b->x + b->w && a->x + a->w >= b->x
                && a->y <= b->y + b->h && a->y + a->h >= b->h;

        /*       
        rect1.x < rect2.x + rect2.w &&
        rect1.x + rect1.w > rect2.x &&
        rect1.y < rect2.y + rect2.h &&
        rect1.h + rect1.y > rect2.y
        */
}