#include <stdio.h>

#define HARRYLIB_IMPLEMENTATION
#include "harrylib.h"

#include "scenes.h"

#define WINDOW_TITLE "Square Game v1.0.0-dev"
#define WINDOW_SIZE 160
#define WINDOW_SCALE 5

/*
TODO:

- Fix bug where player shoots down screen, probably something wrong with
  event handling code.
*/

scene_res_t* scene_res;

void
main_loop(void) {
    hl_poll_events();
    hl_begin_draw();

    hl_clear(HL_GB1);

    scene_l1_update(scene_res);
    scene_l1_draw(scene_res);

    hl_end_draw();
}

int
main(void) {
    hl_result_t r;

    r = hl_open_window(
        WINDOW_TITLE,
        WINDOW_SIZE * WINDOW_SCALE, 
        WINDOW_SIZE * WINDOW_SCALE
    );
    if (r.flag == HL_RESULT_ERROR) {
        fprintf(stderr, "[squaregame] error: %s", r.err);
    } else {
        hl_scale_window(WINDOW_SCALE, WINDOW_SCALE);

        scene_res = scene_load_res();

        scene_l1_load(scene_res);
        while(!hl_window_should_close()) {
            main_loop();
            hl_delay(16);
        }
        scene_l1_unload(scene_res);

        scene_unload_res(scene_res);
    }

    hl_close_window();

    return 0;
}