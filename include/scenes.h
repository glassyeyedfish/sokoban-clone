#ifndef SCENES_H
#define SCENES_H

#include "harrylib.h"

typedef struct {
    hl_font_t* font;
} scene_res_t;

scene_res_t* scene_load_res(void);
void scene_unload_res(scene_res_t* scene_res);

void scene_l1_load(scene_res_t* scene_res);
void scene_l1_update(scene_res_t* scene_res);
void scene_l1_draw(scene_res_t* scene_res);
void scene_l1_unload(scene_res_t* scene_res);

#endif /* SCENES_H */