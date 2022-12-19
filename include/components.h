#ifndef COMPONENTS_H
#define COMPONENTS_H

#include<stdbool.h>

typedef enum {
    DIRECTION_IDLE,
    DIRECTION_RIGHT,
    DIRECTION_LEFT,
    DIRECTION_DOWN,
    DIRECTION_UP
} direction_t;

typedef struct {
    float x;
    float y;
    float w;
    float h;
} aabb_t;

bool aabb_is_overlapping(aabb_t a, aabb_t b);
aabb_t aabb_resolve_collision(aabb_t collider, direction_t collider_direction, 
    aabb_t collidee);


#endif
