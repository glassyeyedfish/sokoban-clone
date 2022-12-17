#include "components.h"
#include "entities.h"
#include "harrylib.h"

button_t 
button_new(int x, int y) {
    return (button_t) {
        (aabb_t) {x, y, 16, 16}
    };
}

void 
button_draw(button_t* button) {
    hl_fill_rect(
        (hl_rect_t) {
            button->aabb.x + 4, 
            button->aabb.y + 4, 
            8, 
            8 
        },
        HL_GB2
    );
}
