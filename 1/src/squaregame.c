#include <stdio.h>

#include <SDL2/SDL.h>

#include "result.h"
#include "sdl.h"

int
main(void) {
        result_t r;
        
        sdl_context_t ctx;

        r = sdl_init_context(&ctx);
        if (r.result == RESULT_ERROR) {
                fprintf(stderr, "[squaregame] error: %s", r.err);
        }

        while(!ctx.window_should_close) {
                sdl_poll_events(&ctx);

                SDL_RenderClear(ctx.renderer);
                SDL_RenderPresent(ctx.renderer);

                SDL_Delay(16);
        }

        sdl_quit_context(&ctx);

        return 0;
}