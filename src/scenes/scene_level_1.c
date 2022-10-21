#include <stdio.h>
#include <stdlib.h>

#include "entities.h"
#include "scenes.h"

struct level_1 {
        player_t player;
        wall_t wall;
        int delete_me;
};

static struct level_1* scene;

void
scene_l1_load(void) {
        scene = malloc(sizeof(struct level_1));
        scene->player = player_new(16, 16);
        scene->wall = wall_new(64, 64, 16, 16);
        scene->delete_me = 0;
}

void
scene_l1_draw(void) {
        scene->delete_me = (scene->delete_me + 1) % 100;

        player_move(&scene->player);

        if (aabb_is_overlapping(
                &scene->player.aabb,
                &scene->wall.aabb
        )) {
                printf("%d\n", scene->delete_me);
        }

        player_draw(&scene->player);
        wall_draw(&scene->wall);
}

void
scene_l1_unload(void) {
        free(scene);
}