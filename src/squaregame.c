#include <stdio.h>

#include "harrylib.h"
#include "result.h"
#include "scenes.h"

#define WINDOW_SIZE 160
#define WINDOW_SCALE 5

/*
TODO:

- Fix bug where player shoots down screen, probably something wrong with
  event handling code.
*/

void
main_loop(void) {
        hl_poll_events();
        hl_begin_draw();

        hl_clear(HL_BLACK);

        scene_l1_update();
        scene_l1_draw();

        hl_end_draw();
}

int
main(void) {
        result_t r;

        r = hl_open_window(
                "Square Game V1", 
                WINDOW_SIZE * WINDOW_SCALE, 
                WINDOW_SIZE * WINDOW_SCALE
        );
        if (r.result == RESULT_ERROR) {
                fprintf(stderr, "[squaregame] error: %s", r.err);
        } else {
                hl_scale_window(WINDOW_SCALE, WINDOW_SCALE);
                scene_l1_load();
                while(!hl_window_should_close()) {
                        main_loop();
                        hl_delay(16);
                }
                scene_l1_unload();
        }

        hl_close_window();

        return 0;
}