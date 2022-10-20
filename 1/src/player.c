#include <SDL2/SDL.h>

#include "player.h"
#include "sdl.h"

player_t 
player_new(void) {
        player_t player;
        SDL_Rect rect;

        player.x = 0;
        player.y = 0;

        rect.x = 1;
        rect.y = 1;
        rect.w = 14;
        rect.h = 14;

        player.rect = rect;

        return player;
}
void 
player_move(player_t* player, sdl_context_t* ctx) {
        if (sdl_is_key_pressed(ctx, SDL_KEYDOWN)) {
                player->y += 16;
                player->rect.y += 16;
        }
}