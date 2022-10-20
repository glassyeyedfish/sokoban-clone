#include "components.h"
#include "entities.h"
#include "harrylib.h"

player_t 
player_new(int x, int y) {
        return (player_t) {
                x,
                y,
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
        if (hl_is_key_down(HL_KEY_RIGHT)) {
                player->x += 1;
                player->aabb.x += 1;
        } else if (hl_is_key_down(HL_KEY_LEFT)) {
                player->x -= 1;
                player->aabb.x -= 1;
        } else if (hl_is_key_down(HL_KEY_DOWN)) {
                player->y += 1;
                player->aabb.y += 1;
        } else if (hl_is_key_down(HL_KEY_UP)) {
                player->y -= 1;
                player->aabb.y -= 1;
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
