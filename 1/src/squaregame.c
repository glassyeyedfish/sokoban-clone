#include <stdio.h>

#include "result.h"
#include "harrylib.h"

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

        hl_end_draw();
}

int
main(void) {
        result_t r;

        r = hl_open_window();
        if (r.result == RESULT_ERROR) {
                fprintf(stderr, "[squaregame] error: %s", r.err);
        }

        while(!hl_window_should_close()) {
                main_loop();
                hl_delay(16);
        }

        hl_close_window();

        return 0;
}