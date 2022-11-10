#include "components.h"
#include "entities.h"
#include "harrylib.h"

block_t 
block_new(int x, int y) {
    return (block_t) {
        DIRECTION_IDLE,
        (aabb_t) {x, y, 16, 16}
    };
}

void 
block_draw(block_t* block) {
    hl_draw_rect(
        (hl_rect_t) {
            block->aabb.x + 1, 
            block->aabb.y + 1, 
            14, 
            14 
        },
        HL_GB2
    );
}