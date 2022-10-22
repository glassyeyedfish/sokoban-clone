#include "components.h"
#include "entities.h"
#include "harrylib.h"

block_t 
block_new(int x, int y) {
        return (block_t) {
                x,
                y,
                DIRECTION_IDLE,
                (aabb_t) {x, y, 16, 16}
        };
}

void 
block_resolve_collision(block_t* block, aabb_t* a) {
        if (block->direction == DIRECTION_RIGHT) {
                block->x = a->x - 16;
                block->aabb.x = block->x + 1;
        } else if (block->direction == DIRECTION_LEFT) {
                block->x = a->x + a->w;
                block->aabb.x = block->x + 1;
        } else if (block->direction == DIRECTION_DOWN) {
                block->y = a->y - 16;
                block->aabb.y = block->y + 1;
        } else if (block->direction == DIRECTION_UP) {
                block->y = a->y + a->h;
                block->aabb.y = block->y + 1;
        }
}

void 
block_draw(block_t* block) {
        hl_draw_rect(
                (hl_rect_t) {
                        block->x + 1, 
                        block->y + 1, 
                        14, 
                        14 
                },
                HL_WHITE
        );
        hl_draw_rect(
                (hl_rect_t) {
                        block->x + 2, 
                        block->y + 2, 
                        12, 
                        12 
                },
                HL_WHITE
        );
}