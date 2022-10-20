#include <stdlib.h>

#include "entities.h"
#include "scenes.h"

struct level_1 {
        player_t player;
};

static struct level_1* scene;

void
scene_l1_load(void) {
        scene = malloc(sizeof(struct level_1));
        scene->player = player_new(16, 16);
}

void
scene_l1_draw(void) {
        player_move(&scene->player);
        player_draw(&scene->player);
}

void
scene_l1_unload(void) {
        free(scene);
}