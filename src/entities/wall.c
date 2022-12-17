#include "components.h"
#include "entities.h"
#include "harrylib.h"

wall_t 
wall_new(int x, int y, int w, int h) {
    return (wall_t) {
        (aabb_t) {x, y, w, h}
    };
}

void 
wall_draw(wall_t* wall) {
    hl_fill_rect(
        (hl_rect_t) {
            wall->aabb.x, 
            wall->aabb.y, 
            wall->aabb.w, 
            wall->aabb.h 
        },
        HL_GB0
    );
}
