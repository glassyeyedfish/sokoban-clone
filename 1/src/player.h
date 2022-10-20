#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

#include "sdl.h"

typedef struct {
        int x;
        int y;
        SDL_Rect rect;
} player_t;

player_t player_new(void);
void player_move(player_t* player, sdl_context_t* ctx);

#endif