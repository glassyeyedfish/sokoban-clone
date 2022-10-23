#include "components.h"

int
aabb_is_overlapping(aabb_t a, aabb_t b) {
        return     a.x < b.x + b.w 
                && a.x + a.w > b.x
                && a.y < b.y + b.h 
                && a.y + a.h > b.y;
}

aabb_t
aabb_resolve_collision(
        aabb_t collider, 
        direction_t collider_direction, 
        aabb_t collidee
) {
        if (collider_direction == DIRECTION_RIGHT) {
                collider.x = collidee.x - 16;
        } else if (collider_direction == DIRECTION_LEFT) {
                collider.x = collidee.x + collidee.w;
        } else if (collider_direction == DIRECTION_DOWN) {
                collider.y = collidee.y - 16;
        } else if (collider_direction == DIRECTION_UP) {
                collider.y = collidee.y + collidee.h;
        }

        return collider;
}