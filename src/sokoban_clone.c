#include <stdio.h>

#define HARRYLIB_IMPLEMENTATION
#include "harrylib.h"

#include "scenes.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

#define WINDOW_TITLE "Sokoban Clone v1.0.1-dev"
#define WINDOW_SIZE 160
#define WINDOW_SCALE 5

/*
TODO:

- Fix bug where player shoots down screen, probably something wrong with
  event handling code.
*/

scene_res_t* scene_res;
scene_name_t current_scene;
scene_name_t next_scene;

void
main_loop(void) {
    hl_poll_events();
    hl_begin_draw();

    hl_clear(HL_GB1);

    switch(current_scene) {

    case SCENE_MAIN_MENU:
        next_scene = scene_mm_update(scene_res);
        scene_mm_draw(scene_res);
        break;

    case SCENE_LEVEL_0:
        next_scene = scene_l0_update(scene_res);
        scene_l0_draw(scene_res);
        break;

    case SCENE_LEVEL_1:
        next_scene = scene_l1_update(scene_res);
        scene_l1_draw(scene_res);
        break;

    case SCENE_WIN:
        next_scene = scene_w_update(scene_res);
        scene_w_draw(scene_res);
        break;

    default:
        break;
    }

    if (next_scene != current_scene) {

        /* Unload current scene */
        switch(current_scene) {

        case SCENE_MAIN_MENU:
            scene_mm_unload(scene_res);
            break;

        case SCENE_LEVEL_0:
            scene_l0_unload(scene_res);
            break;

        case SCENE_LEVEL_1:
            scene_l1_unload(scene_res);
            break;

        case SCENE_WIN:
            scene_w_unload(scene_res);
            break;

        default:
            break;
        }

        /* Load the next scene */
        switch(next_scene) {

        case SCENE_MAIN_MENU:
            scene_mm_load(scene_res);
            break;

        case SCENE_LEVEL_0:
            scene_l0_load(scene_res);
            break;

        case SCENE_LEVEL_1:
            scene_l1_load(scene_res);
            break;

        case SCENE_WIN:
            scene_w_load(scene_res);
            break;

        default:
            break;
        }

        current_scene = next_scene;
    }

    hl_end_draw();
}

int
main(void) {
    if (
        hl_open_window(WINDOW_TITLE, WINDOW_SIZE * WINDOW_SCALE, 
        WINDOW_SIZE * WINDOW_SCALE) == 0 
    ) {
        hl_scale_window(WINDOW_SCALE, WINDOW_SCALE);

        scene_res = scene_load_res();
        current_scene = SCENE_MAIN_MENU;
        next_scene = SCENE_MAIN_MENU;

        scene_mm_load(scene_res);

#ifdef __EMSCRIPTEN__

        emscripten_set_main_loop(main_loop, 0, 1);

#else

        while(!hl_window_should_close()) {
            main_loop();
            hl_delay(16);
        }

#endif

        switch(current_scene) {

        case SCENE_MAIN_MENU:
            scene_mm_unload(scene_res);
            break;

        case SCENE_LEVEL_0:
            scene_l0_unload(scene_res);
            break;

        case SCENE_LEVEL_1:
            scene_l1_unload(scene_res);
            break;

        case SCENE_WIN:
            scene_w_unload(scene_res);
            break;

        default:
            break;
        }

        scene_unload_res(scene_res);

        hl_close_window();
    }


    return 0;
}
