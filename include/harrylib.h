#ifndef HARRYLIB_H
#define HARRYLIB_H

#define HL_KEYCODE_MOD 1073741625 
#define HL_KEYCODE_MAX 512

#include<stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/*
================================================================================
================================================================================


    DECLARATIONS


================================================================================
================================================================================
*/

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;

    int window_should_close;
    SDL_KeyCode current_key_state[512];
    SDL_KeyCode previous_key_state[512];
} hl_context_t;

typedef enum {
    HL_KEY_BKSP    = 8,
    HL_KEY_TAB     = 9,
    HL_KEY_RETURN  = 13,
    HL_KEY_ESC     = 27,
    HL_KEY_SPACE   = 32,
    HL_KEY_0       = 48,
    HL_KEY_1, HL_KEY_2, HL_KEY_3,
    HL_KEY_4, HL_KEY_5, HL_KEY_6,
    HL_KEY_7, HL_KEY_8, HL_KEY_9,
    HL_KEY_A       = 97,
    HL_KEY_B, HL_KEY_C, HL_KEY_D, HL_KEY_E, HL_KEY_F,
    HL_KEY_G, HL_KEY_H, HL_KEY_I, HL_KEY_J, HL_KEY_K,
    HL_KEY_L, HL_KEY_M, HL_KEY_N, HL_KEY_O, HL_KEY_P,
    HL_KEY_Q, HL_KEY_R, HL_KEY_S, HL_KEY_T, HL_KEY_U,
    HL_KEY_V, HL_KEY_W, HL_KEY_X, HL_KEY_Y, HL_KEY_Z,
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
    SDL_Texture* font_atlas;
    int char_w;
    int char_h;
} hl_font_t;

// The OFFICIAL color orange for the library.
#define HL_ORANGE (hl_color_t) { 255, 115,   0, 255 }

#define HL_BLACK (hl_color_t) {   0,   0,   0, 255 }
#define HL_WHITE (hl_color_t) { 255, 255, 255, 255 }

#define HL_GREEN (hl_color_t) {   0, 255,   0, 255 }

#define HL_GB0 (hl_color_t) {  12,  14,  10, 255 }
#define HL_GB1 (hl_color_t) {  32,  34,  30, 255 }
#define HL_GB2 (hl_color_t) { 130, 135, 132, 255 }
#define HL_GB3 (hl_color_t) { 200, 204, 202, 255 }

/* window */
int hl_open_window(const char* title, int width, int height);
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

/* font */
hl_font_t* hl_load_bitmap_font(const char* path, int char_w, int char_h);
void hl_unload_font(hl_font_t* font);
void hl_draw_font_atlas(hl_font_t* font);

/* text */
void hl_draw_text(hl_font_t* font, const char* text, int x, int y, hl_color_t color);

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

int
hl_open_window(const char* title, int width, int height) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL Error: %s", SDL_GetError());
        return -1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        fprintf(stderr, "IMG Error: %s", IMG_GetError());
        return -1;
    }

    if (TTF_Init() < 0) {
        fprintf(stderr, "TTF Error: %s", TTF_GetError());
        return -1;
    }

    ctx.window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height, 0);

    if (ctx.window == NULL) {
        fprintf(stderr, "SDL Error: %s", SDL_GetError());
        return -1;
    }

    ctx.renderer = SDL_CreateRenderer(ctx.window, -1, 0);

    if (ctx.renderer == NULL) {
        fprintf(stderr, "SDL Error: %s", SDL_GetError());
        return -1;
    }

    ctx.window_should_close = 0;

    return 0;
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

/*
================================================================================

    FONT

================================================================================
*/

hl_font_t* hl_load_bitmap_font(const char* path, int char_w, int char_h) {
    hl_font_t* font = malloc(sizeof(hl_font_t));
    SDL_Surface* surface;

    surface = IMG_Load(path);

    font->font_atlas = SDL_CreateTextureFromSurface(ctx.renderer, surface);
    font->char_w = char_w;
    font->char_h = char_h;

    SDL_FreeSurface(surface);


    return font;
}

void hl_unload_font(hl_font_t* font) {
    SDL_DestroyTexture(font->font_atlas);
    free(font);
}

void hl_draw_font_atlas(hl_font_t* font) {
    SDL_RenderCopy(ctx.renderer, font->font_atlas, NULL, NULL);
}

/*
================================================================================

    TEXT

================================================================================
*/

void hl_draw_text(hl_font_t* font, const char* text, int x, int y, hl_color_t color) {
    int i;

    SDL_Rect src;
    SDL_Rect dst;

    for (i = 0; text[i] != '\0'; i++) {
        src.x = (text[i] % 16) * font->char_w;
        src.y = (text[i] / 16) * font->char_h;
        src.w = font->char_w;
        src.h = font->char_h;

        dst.x = x + (i * font->char_w);
        dst.y = y;
        dst.w = font->char_w;
        dst.h = font->char_h;

        SDL_SetTextureColorMod(font->font_atlas, color.r, color.g, color.b);
        SDL_SetTextureAlphaMod(font->font_atlas, color.a);
        SDL_RenderCopy(ctx.renderer, font->font_atlas, &src, &dst);
    }

}

#endif /* HARRYLIB_IMPELMENTATION */

#endif /* HARRYLIB_H */
