#include <stdio.h>
#include <stdlib.h>

#include "entities.h"
#include "scenes.h"

void scene_mm_load(scene_res_t* scene_res){}
void scene_mm_reload(scene_res_t* scene_res){}

scene_name_t scene_mm_update(scene_res_t* scene_res){
    if (hl_is_key_pressed(HL_KEY_Z)) return SCENE_LEVEL_0;
    return SCENE_MAIN_MENU;
}

void scene_mm_draw(scene_res_t* scene_res){
    hl_fill_rect((hl_rect_t) {0, 0, 16, 160}, HL_GB0);
    hl_fill_rect((hl_rect_t) {0, 0, 160, 16}, HL_GB0);
    hl_fill_rect((hl_rect_t) {144, 0, 16, 160}, HL_GB0);
    hl_fill_rect((hl_rect_t) {0, 144, 160, 16}, HL_GB0);

    hl_draw_text(scene_res->font, "Sokoban Clone", 28, 48, HL_GB3);
    hl_draw_text(scene_res->font, "Press Z to", 28, 80, HL_GB3);
    hl_draw_text(scene_res->font, "Start", 28, 96, HL_GB3);
}

void scene_mm_unload(scene_res_t* scene_res){}
