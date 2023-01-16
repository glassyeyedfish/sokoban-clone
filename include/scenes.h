#ifndef SCENES_H
#define SCENES_H

#include "harrylib.h"

typedef struct {
    hl_font_t* font;
} scene_res_t;

typedef enum {
    SCENE_MAIN_MENU,
    SCENE_LEVEL_0,
    SCENE_LEVEL_1,
    SCENE_LEVEL_2,
    SCENE_WIN
} scene_name_t;

scene_res_t* scene_load_res(void);
void scene_unload_res(scene_res_t* scene_res);

void scene_mm_load(scene_res_t* scene_res);
void scene_mm_reload(scene_res_t* scene_res);
scene_name_t scene_mm_update(scene_res_t* scene_res);
void scene_mm_draw(scene_res_t* scene_res);
void scene_mm_unload(scene_res_t* scene_res);

void scene_l0_load(scene_res_t* scene_res);
void scene_l0_reload(scene_res_t* scene_res);
scene_name_t scene_l0_update(scene_res_t* scene_res);
void scene_l0_draw(scene_res_t* scene_res);
void scene_l0_unload(scene_res_t* scene_res);

void scene_l1_load(scene_res_t* scene_res);
void scene_l1_reload(scene_res_t* scene_res);
scene_name_t scene_l1_update(scene_res_t* scene_res);
void scene_l1_draw(scene_res_t* scene_res);
void scene_l1_unload(scene_res_t* scene_res);

void scene_l2_load(scene_res_t* scene_res);
void scene_l2_reload(scene_res_t* scene_res);
scene_name_t scene_l2_update(scene_res_t* scene_res);
void scene_l2_draw(scene_res_t* scene_res);
void scene_l2_unload(scene_res_t* scene_res);

void scene_w_load(scene_res_t* scene_res);
void scene_w_reload(scene_res_t* scene_res);
scene_name_t scene_w_update(scene_res_t* scene_res);
void scene_w_draw(scene_res_t* scene_res);
void scene_w_unload(scene_res_t* scene_res);

#endif /* SCENES_H */
