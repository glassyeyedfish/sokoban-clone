#include "components.h"
#include "entities.h"
#include "harrylib.h"

player_t 
player_new(int x, int y) {
    return (player_t) {
        DIRECTION_IDLE,
        (aabb_t) {
            x,
            y,
            16,
            16
        }
    };
}

void 
player_move(player_t* player) {
    if (hl_is_key_pressed(HL_KEY_RIGHT) || hl_is_key_pressed(HL_KEY_D)) {
        player->direction = DIRECTION_RIGHT;
        player->aabb.x += 16;
    } else if (hl_is_key_pressed(HL_KEY_LEFT) || hl_is_key_pressed(HL_KEY_A)) {
        player->direction = DIRECTION_LEFT;
        player->aabb.x -= 16;
    } else if (hl_is_key_pressed(HL_KEY_DOWN) || hl_is_key_pressed(HL_KEY_S)) {
        player->direction = DIRECTION_DOWN;
        player->aabb.y += 16;
    } else if (hl_is_key_pressed(HL_KEY_UP) || hl_is_key_pressed(HL_KEY_W)) {
        player->direction = DIRECTION_UP;
        player->aabb.y -= 16;
    }
}

void
player_draw(player_t* player) {
    /* Back */
    hl_fill_rect(
        (hl_rect_t) {player->aabb.x + 1, player->aabb.y + 1, 14, 14},
        HL_GB1
    );
    

    /* Body */
    hl_draw_rect(
        (hl_rect_t) {player->aabb.x + 1, player->aabb.y + 1, 14, 14},
        HL_GB3
    );

    /* Left Eye */
    hl_draw_rect(
        (hl_rect_t) {player->aabb.x + 5, player->aabb.y + 5, 1, 2},
        HL_GB3
    );

    /* Right Eye */
    hl_draw_rect(
        (hl_rect_t) {player->aabb.x + 10, player->aabb.y + 5, 1, 2},
        HL_GB3
    );

    /* Mouth */
    hl_draw_rect(
        (hl_rect_t) {player->aabb.x + 5, player->aabb.y + 10, 6, 1},
        HL_GB3
    );
}
