#ifndef SCENES_H
#define SCENES_H

#include "harrylib.h"

typedef struct {
    hl_font_t font;
} scene_res_t;

scene_res_t scene_res;

void scene_load_res(void);
void scene_unload_res(void);

void scene_l1_load(void);
void scene_l1_update(void);
void scene_l1_draw(void);
void scene_l1_unload(void);

#endif /* SCENES_H */