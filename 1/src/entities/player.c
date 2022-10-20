#include "entities.h"
#include "harrylib.h"

player_t 
player_new(int x, int y) {
        player_t player;
        player.x = x;
        player.y = y;
        return player;
}

void 
player_move(player_t* player) {
        if (hl_is_key_pressed(HL_KEY_RIGHT)) {
                player->x += 16;
        } else if (hl_is_key_pressed(HL_KEY_LEFT)) {
                player->x -= 16;
        } else if (hl_is_key_pressed(HL_KEY_DOWN)) {
                player->y += 16;
        } else if (hl_is_key_pressed(HL_KEY_UP)) {
                player->y -= 16;
        }
}

void
player_draw(player_t* player) {
        hl_draw_rect(
                (hl_rect_t) {player->x + 1, player->y + 1, 14, 14},
                HL_WHITE
        );
}
