#include <SDL2/SDL.h>

#include "result.h"
#include "harrylib.h"

hl_context_t ctx = { 0 };

/*
================================================================================

        WINDOW

================================================================================
*/

result_void_t
hl_open_window(void) {
        result_void_t r;

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                fprintf(stderr, "SDL Error: %s", SDL_GetError());
                r.result = RESULT_ERROR;
                r.err = "failed to init SDL2";
                return r;
        }

        ctx.window = SDL_CreateWindow(
                "Square Game v1",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                640, 640, 0);

        if (ctx.window == NULL) {
                fprintf(stderr, "SDL Error: %s", SDL_GetError());
                r.result = RESULT_ERROR;
                r.err = "failed to init SDL2 window";
                return r;
        }

        ctx.renderer = SDL_CreateRenderer(ctx.window, -1, 0);

        if (ctx.renderer == NULL) {
                fprintf(stderr, "SDL Error: %s", SDL_GetError());
                r.result = RESULT_ERROR;
                r.err = "failed to init SDL2 renderer";
                return r;
        }

        ctx.window_should_close = 0;

        r.result = RESULT_VOID;
        return r;
}

void 
hl_close_window(void) {
        SDL_DestroyRenderer(ctx.renderer);
        SDL_DestroyWindow(ctx.window);
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

/*
================================================================================

        UTIL

================================================================================
*/

void
hl_delay(unsigned int ms) {
        SDL_Delay(ms);
}

/*
================================================================================

        EVENTS

================================================================================
*/

void
hl_poll_events(void) {
        int i;
        SDL_Event e;

        for (i = 0; i < HL_KEYCODE_MAX; i++) {
                ctx.previous_key_state[i] = ctx.current_key_state[i];
        }

        while (SDL_PollEvent(&e)) {
                switch(e.type) {
                case SDL_WINDOWEVENT:
                        switch(e.window.event) {
                        case SDL_WINDOWEVENT_CLOSE:
                                ctx.window_should_close = 1;
                                break;
                        default:
                                break;
                        }
                        break;

                case SDL_KEYDOWN:
                        for (i = 0; i < 512; i++) {
                                if (e.key.keysym.sym % HL_KEYCODE_MOD == i) {
                                        ctx.current_key_state[i] = 1;
                                }
                        }
                        break;

                case SDL_KEYUP:
                        for (i = 0; i < 512; i++) {
                                if (e.key.keysym.sym % HL_KEYCODE_MOD == i) {
                                        ctx.current_key_state[i] = 0;
                                }
                        }
                        break;

                default:
                        break;
                }
        }
}

int
hl_window_should_close(void) {
        return ctx.window_should_close;
}

int 
hl_is_key_down(hl_key_t key) {
        return ctx.current_key_state[key % HL_KEYCODE_MOD];
}

int 
hl_is_key_pressed(hl_key_t key) {
        return ctx.current_key_state[key % HL_KEYCODE_MOD] 
                && !ctx.previous_key_state[key % HL_KEYCODE_MOD];
}
