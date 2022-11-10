#ifndef HARRYLIB_H
#define HARRYLIB_H

#define HL_KEYCODE_MOD 1073741625 
#define HL_KEYCODE_MAX 512

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/*
================================================================================
================================================================================


    DECLARATIONS


================================================================================
================================================================================
*/

typedef enum { 
    HL_RESULT_OK,
    HL_RESULT_ERROR
} hl_result_flag_t;

typedef struct {
    hl_result_flag_t flag;
    char* err;
} hl_result_t;

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;

    int window_should_close;
    SDL_KeyCode current_key_state[512];
    SDL_KeyCode previous_key_state[512];
} hl_context_t;

typedef enum {
    HL_KEY_RIGHT   = 278,
    HL_KEY_LEFT, HL_KEY_DOWN, HL_KEY_UP
} hl_key_t;

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} hl_color_t;

typedef struct {
    int x;
    int y;
    int w;
    int h;
} hl_rect_t;

typedef struct {
    TTF_Font* font;
} hl_font_t;

#define HL_BLACK (hl_color_t) {   0,   0,   0, 255 }
#define HL_WHITE (hl_color_t) { 255, 255, 255, 255 }

#define HL_GREEN (hl_color_t) {   0, 255,   0, 255 }

#define HL_GB0 (hl_color_t) {  12,  14,  10, 255 }
#define HL_GB1 (hl_color_t) {  32,  34,  30, 255 }
#define HL_GB2 (hl_color_t) { 130, 135, 132, 255 }
#define HL_GB3 (hl_color_t) { 200, 204, 202, 255 }

/* window */
hl_result_t hl_open_window(const char* title, int width, int height);
void hl_close_window(void);
void hl_scale_window(float x, float y);

/* util */
void hl_delay(unsigned int ms);

/* events */
void hl_poll_events(void);
int hl_window_should_close(void);
int hl_is_key_down(hl_key_t key);
int hl_is_key_pressed(hl_key_t key);

/* drawing */
void hl_begin_draw(void);
void hl_end_draw(void);
void hl_clear(hl_color_t color);

/* shapes */
void hl_draw_rect(hl_rect_t rect, hl_color_t color);
void hl_fill_rect(hl_rect_t rect, hl_color_t color);

#ifdef HARRYLIB_IMPLEMENTATION

/*
================================================================================
================================================================================


    IMPLEMENTATIONS


================================================================================
================================================================================
*/

hl_context_t ctx = { 0 };

/*
================================================================================

    WINDOW

================================================================================
*/

hl_result_t
hl_open_window(const char* title, int width, int height) {
    hl_result_t r;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL Error: %s", SDL_GetError());
        r.flag = HL_RESULT_ERROR;
        r.err = "failed to init SDL";
        return r;
    }

    if (TTF_Init() < 0) {
        fprintf(stderr, "TTF Error: %s", TTF_GetError());
        r.flag = HL_RESULT_ERROR;
        r.err = "failed to init SDL_ttf";
        return r;
    }

    ctx.window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height, 0);

    if (ctx.window == NULL) {
        fprintf(stderr, "SDL Error: %s", SDL_GetError());
        r.flag = HL_RESULT_ERROR;
        r.err = "failed to init SDL window";
        return r;
    }

    ctx.renderer = SDL_CreateRenderer(ctx.window, -1, 0);

    if (ctx.renderer == NULL) {
        fprintf(stderr, "SDL Error: %s", SDL_GetError());
        r.flag = HL_RESULT_ERROR;
        r.err = "failed to init SDL renderer";
        return r;
    }

    ctx.window_should_close = 0;

    r.flag = HL_RESULT_OK;
    return r;
}

void 
hl_close_window(void) {
    SDL_DestroyRenderer(ctx.renderer);
    SDL_DestroyWindow(ctx.window);

    TTF_Quit();
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void 
hl_scale_window(float x, float y) {
    SDL_RenderSetScale(ctx.renderer, x, y);
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

#endif /* HARRYLIB_IMPELMENTATION */

#endif /* HARRYLIB_H */