#include <stdio.h>

#include <SDL2/SDL.h>

#include "player.h"
#include "result.h"
#include "sdl.h"

/*
TODO:

- Fix bug where player shoots down screen, probably something wrong with
  event handling code.
*/

int
main(void) {
        result_t r;
        
        sdl_context_t ctx;

        player_t player;

        r = sdl_init_context(&ctx);
        if (r.result == RESULT_ERROR) {
                fprintf(stderr, "[squaregame] error: %s", r.err);
        }

        SDL_RenderSetScale(ctx.renderer, 4.0, 4.0);

        player = player_new();

        while(!ctx.window_should_close) {
                sdl_poll_events(&ctx);

                player_move(&player, &ctx);

                SDL_SetRenderDrawColor(ctx.renderer, 0, 0, 0, 255);
                SDL_RenderClear(ctx.renderer);

                SDL_SetRenderDrawColor(ctx.renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(ctx.renderer, &player.rect);

                SDL_RenderPresent(ctx.renderer);
                SDL_Delay(100);
        }

        sdl_quit_context(&ctx);

        return 0;
}