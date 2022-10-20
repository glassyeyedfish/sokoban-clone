#ifndef HARRYLIB_H
#define HARRYLIB_H

#define HL_KEYCODE_MOD 1073741625 
#define HL_KEYCODE_MAX 512

#include <SDL2/SDL.h>

#include "result.h"

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

#define HL_BLACK (hl_color_t) {   0,   0,   0, 255 }
#define HL_WHITE (hl_color_t) { 255, 255, 255, 255 }

/* window */
result_void_t hl_open_window(const char* title, int width, int height);
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

#endif