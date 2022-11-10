#ifndef SCENES_H
#define SCENES_H

#include "harrylib.h"

typedef struct {
    hl_font_t font;
} scene_res_t;

void scene_load_res(scene_res_t* res);
void scene_unload_res(scene_res_t* res);

void scene_l1_load(void);
void scene_l1_update(void);
void scene_l1_draw(void);
void scene_l1_unload(void);

#endif