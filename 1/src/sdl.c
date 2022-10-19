#include <SDL2/SDL.h>

#include "result.h"
#include "sdl.h"

result_void_t
sdl_init_context(sdl_context_t* ctx) {
        result_void_t r;

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                fprintf(stderr, "SDL Error: %s", SDL_GetError());
                r.result = RESULT_ERROR;
                r.err = "failed to init SDL2";
                return r;
        }

        ctx->window = SDL_CreateWindow(
                "Square Game v1",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                640, 640, 0);

        if (ctx->window == NULL) {
                fprintf(stderr, "SDL Error: %s", SDL_GetError());
                r.result = RESULT_ERROR;
                r.err = "failed to init SDL2 window";
                return r;
        }

        ctx->renderer = SDL_CreateRenderer(ctx->window, -1, 0);

        if (ctx->renderer == NULL) {
                fprintf(stderr, "SDL Error: %s", SDL_GetError());
                r.result = RESULT_ERROR;
                r.err = "failed to init SDL2 renderer";
                return r;
        }

        ctx->window_should_close = 0;

        r.result = RESULT_VOID;
        return r;
}

void 
sdl_quit_context(sdl_context_t* ctx) {
        SDL_DestroyWindow(ctx->window);
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void
sdl_poll_events(sdl_context_t* ctx) {
        int i;
        SDL_Event e;

        for (i = 0; i < KEYCODE_MAX; i++) {
                ctx->previous_key_state[i] = ctx->current_key_state[i];
        }

        while (SDL_PollEvent(&e)) {
                switch(e.type) {
                case SDL_WINDOWEVENT:
                        switch(e.window.event) {
                        case SDL_WINDOWEVENT_CLOSE:
                                ctx->window_should_close = 1;
                                break;
                        default:
                                break;
                        }
                        break;

                case SDL_KEYDOWN:
                        for (i = 0; i < 512; i++) {
                                if (e.key.keysym.sym % KEYCODE_MOD == i) {
                                        ctx->current_key_state[i] = 1;
                                }
                        }
                        break;

                case SDL_KEYUP:
                        for (i = 0; i < 512; i++) {
                                if (e.key.keysym.sym % KEYCODE_MOD == i) {
                                        ctx->current_key_state[i] = 0;
                                }
                        }
                        break;

                default:
                        break;
                }
        }
}

int 
sdl_is_key_down(sdl_context_t* ctx, SDL_KeyCode key) {
        return ctx->current_key_state[key % KEYCODE_MOD];
}

int 
sdl_is_key_pressed(sdl_context_t* ctx, SDL_KeyCode key) {
        return ctx->current_key_state[key % KEYCODE_MOD] 
                && !ctx->previous_key_state[key % KEYCODE_MOD];
}