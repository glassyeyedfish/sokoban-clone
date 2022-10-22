#include "components.h"
#include "entities.h"
#include "harrylib.h"

player_t 
player_new(int x, int y) {
        return (player_t) {
                x,
                y,
                DIRECTION_IDLE,
                (aabb_t) {
                        x + 1,
                        y + 1,
                        14,
                        14
                }
        };
}

void 
player_move(player_t* player) {
        if (hl_is_key_pressed(HL_KEY_RIGHT)) {
                player->direction = DIRECTION_RIGHT;
                player->x += 16;
                player->aabb.x += 16;
        } else if (hl_is_key_pressed(HL_KEY_LEFT)) {
                player->direction = DIRECTION_LEFT;
                player->x -= 16;
                player->aabb.x -= 16;
        } else if (hl_is_key_pressed(HL_KEY_DOWN)) {
                player->direction = DIRECTION_DOWN;
                player->y += 16;
                player->aabb.y += 16;
        } else if (hl_is_key_pressed(HL_KEY_UP)) {
                player->direction = DIRECTION_UP;
                player->y -= 16;
                player->aabb.y -= 16;
        }
}

void 
player_resolve_collision(player_t* player, aabb_t* a) {
        if (player->direction == DIRECTION_RIGHT) {
                player->x = a->x - 16;
                player->aabb.x = player->x + 1;
        } else if (player->direction == DIRECTION_LEFT) {
                player->x = a->x + a->w;
                player->aabb.x = player->x + 1;
        } else if (player->direction == DIRECTION_DOWN) {
                player->y = a->y - 16;
                player->aabb.y = player->y + 1;
        } else if (player->direction == DIRECTION_UP) {
                player->y = a->y + a->h;
                player->aabb.y = player->y + 1;
        }
}

void
player_draw(player_t* player) {
        hl_draw_rect(
                (hl_rect_t) {
                        player->aabb.x, 
                        player->aabb.y, 
                        player->aabb.w, 
                        player->aabb.h 
                },
                HL_WHITE
        );
}
