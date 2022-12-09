#include "harrylib.h"
#include "scenes.h"

scene_res_t* scene_load_res(void) {
    scene_res_t* scene_res = malloc(sizeof(scene_res_t));
    scene_res->font = hl_load_bitmap_font("res/font.png", 8, 8);
    return scene_res;
}

void scene_unload_res(scene_res_t* scene_res) {
    hl_unload_font(scene_res->font);
    free(scene_res);
}