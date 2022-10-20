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

/*
================================================================================

        SHAPES

================================================================================
*/

void 
hl_draw_rect(hl_rect_t rect, hl_color_t color) {
        SDL_SetRenderDrawColor(
                ctx.renderer, 
                color.r, 
                color.g, 
                color.b,
                color.a
        );
        SDL_RenderDrawRect(ctx.renderer, (SDL_Rect*) &rect);
}

void 
hl_fill_rect(hl_rect_t rect, hl_color_t color) {
        SDL_SetRenderDrawColor(
                ctx.renderer, 
                color.r, 
                color.g, 
                color.b,
                color.a
        );
        SDL_RenderFillRect(ctx.renderer, (SDL_Rect*) &rect);
}
