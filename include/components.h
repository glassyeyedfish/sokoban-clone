#ifndef COMPONENTS_H
#define COMPONENTS_H

typedef enum {
        DIRECTION_IDLE,
        DIRECTION_RIGHT,
        DIRECTION_LEFT,
        DIRECTION_DOWN,
        DIRECTION_UP
} direction_t;

typedef struct {
        int x;
        int y;
        int w;
        int h;
} aabb_t;

int aabb_is_overlapping(aabb_t a, aabb_t b);
aabb_t aabb_resolve_collision(aabb_t collider, direction_t collider_direction, 
        aabb_t collidee);


#endif