#include <stdio.h>
#include <stdlib.h>

#include "entities.h"
#include "scenes.h"

struct level_1 {
        player_t player;
        wall_t wall[4];
        block_t block;
        int delete_me;
};

static struct level_1* scene;

void
scene_l1_load(void) {
        scene = malloc(sizeof(struct level_1));
        scene->player = player_new(64, 64);

        scene->wall[0] = wall_new(0, 0, 16, 160);
        scene->wall[1] = wall_new(0, 0, 160, 16);
        scene->wall[2] = wall_new(144, 0, 16, 160);
        scene->wall[3] = wall_new(0, 144, 160, 16);

        scene->block = block_new(96, 96);

        scene->delete_me = 0;
}

void
scene_l1_draw(void) {
        scene->delete_me = (scene->delete_me + 1) % 100;

        player_move(&scene->player);

        for (int i = 0; i < 4; i++) {
                if (aabb_is_overlapping(
                        scene->player.aabb, 
                        scene->wall[i].aabb
                )) {
                        scene->player.aabb = aabb_resolve_collision(
                                scene->player.aabb, 
                                scene->player.direction,
                                scene->wall[i].aabb
                        );
                }
                wall_draw(&scene->wall[i]);
        }

        block_draw(&scene->block);
        player_draw(&scene->player);
}

void
scene_l1_unload(void) {
        free(scene);
}