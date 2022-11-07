#include <stdio.h>
#include <stdlib.h>

#include "entities.h"
#include "scenes.h"

#define L1_WALL_COUNT (4)

struct scene_data {
        player_t player;
        wall_t wall[L1_WALL_COUNT];
        block_t block;
};

static struct scene_data* s;

void
scene_l1_load(void) {
        s = malloc(sizeof(struct scene_data));
        s->player = player_new(64, 64);

        s->wall[0] = wall_new(0, 0, 16, 160);
        s->wall[1] = wall_new(0, 0, 160, 16);
        s->wall[2] = wall_new(144, 0, 16, 160);
        s->wall[3] = wall_new(0, 144, 160, 16);

        s->block = block_new(96, 96);
}

void 
scene_l1_update(void) {
        player_move(&s->player);

        for (int i = 0; i < L1_WALL_COUNT; i++) {
                if (aabb_is_overlapping(
                        s->player.aabb, 
                        s->wall[i].aabb
                )) {
                        s->player.aabb = aabb_resolve_collision(
                                s->player.aabb, 
                                s->player.direction,
                                s->wall[i].aabb
                        );
                }
        }
}

void
scene_l1_draw(void) {

        for (int i = 0; i < L1_WALL_COUNT; i++) {
                wall_draw(&s->wall[i]);
        }

        block_draw(&s->block);
        player_draw(&s->player);
}

void
scene_l1_unload(void) {
        free(s);
}