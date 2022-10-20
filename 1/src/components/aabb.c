#include "components.h"

int
aabb_is_overlapping(aabb_t* a, aabb_t* b) {
        return (b->x <= a->x + a->w && b->y + b->h >= a->y);
}