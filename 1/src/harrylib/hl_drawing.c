#include <SDL2/SDL.h>

#include "harrylib.h"

extern hl_context_t ctx;

/*
================================================================================

        DRAWING

================================================================================
*/

void
hl_begin_draw(void) {}

void
hl_end_draw(void) {
        SDL_RenderPresent(ctx.renderer);
}

void
hl_clear(hl_color_t color) {
        SDL_SetRenderDrawColor(
                ctx.renderer, 
                color.r, 
                color.g, 
                color.b,
                color.a
        );
        SDL_RenderClear(ctx.renderer);
}
