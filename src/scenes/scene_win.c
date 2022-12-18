#include <stdio.h>
#include <stdlib.h>

#include "entities.h"
#include "scenes.h"

void scene_w_load(scene_res_t* scene_res){}
void scene_w_reload(scene_res_t* scene_res){}

scene_name_t scene_w_update(scene_res_t* scene_res){
    if (hl_is_key_pressed(HL_KEY_Z)) return SCENE_MAIN_MENU;
    return SCENE_WIN;
}

void scene_w_draw(scene_res_t* scene_res){
    hl_fill_rect((hl_rect_t) {0, 0, 16, 160}, HL_GB0);
    hl_fill_rect((hl_rect_t) {0, 0, 160, 16}, HL_GB0);
    hl_fill_rect((hl_rect_t) {144, 0, 16, 160}, HL_GB0);
    hl_fill_rect((hl_rect_t) {0, 144, 160, 16}, HL_GB0);

    hl_draw_text(scene_res->font, "You win!", 28, 48, HL_GB3);
    hl_draw_text(scene_res->font, "Press Z to go", 28, 80, HL_GB3);
    hl_draw_text(scene_res->font, "back to menu.", 28, 96, HL_GB3);
}

void scene_w_unload(scene_res_t* scene_res){}
