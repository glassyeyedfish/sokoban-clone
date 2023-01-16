#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "entities.h"
#include "scenes.h"

#define L1_WALL_COUNT (6)
#define L1_BLOCK_COUNT (2)

struct scene_data {
    player_t player;
    wall_t wall[L1_WALL_COUNT];
    block_t block[L1_BLOCK_COUNT];
    button_t button[L1_BLOCK_COUNT];
    bool level_is_complete;
};

static struct scene_data* s;

void
scene_l2_load(scene_res_t* scene_res) {
    s = malloc(sizeof(struct scene_data));
    scene_l2_reload(scene_res);
}

void
scene_l2_reload(scene_res_t* scene_res) {
    s->player = player_new(32, 64);

    s->wall[0] = wall_new(  0,   0,  32, 160);
    s->wall[1] = wall_new(  0,   0, 160, 32);
    s->wall[2] = wall_new(6*16,   0,  4*16, 160);
    s->wall[3] = wall_new(  0, 128, 160, 64);
    s->wall[4] = wall_new( 32,  32, 32, 32);
    s->wall[5] = wall_new(2*16, 6*16, 32, 32);

    s->block[0] = block_new(4*16, 3*16);
    s->block[1] = block_new(3*16, 4*16);

    s->button[0] = button_new(4*16, 4*16);
    s->button[1] = button_new(5*16, 6*16);

    s->level_is_complete = false;
}

scene_name_t 
scene_l2_update(scene_res_t* scene_res) {
    s->level_is_complete = true;

    if (hl_is_key_pressed(HL_KEY_X)) {
        scene_l2_reload(scene_res);
    }


    player_move(&s->player);

    // Player collision with walls
    for (int i = 0; i < L1_WALL_COUNT; i++) {
        if (aabb_is_overlapping(s->player.aabb, s->wall[i].aabb)) {
            s->player.aabb = aabb_resolve_collision(
            s->player.aabb, 
            s->player.direction,
            s->wall[i].aabb
            );
        }
    }

    // Player pushing block
    for (int i = 0; i < L1_BLOCK_COUNT; i++) {
        if (aabb_is_overlapping(s->player.aabb, s->block[i].aabb)) {
            switch(s->player.direction) {
            case DIRECTION_RIGHT:
            s->block[i].aabb.x += 16;
            break;
            case DIRECTION_LEFT:
            s->block[i].aabb.x -= 16;
            break;
            case DIRECTION_DOWN:
            s->block[i].aabb.y += 16;
            break;
            case DIRECTION_UP:
            s->block[i].aabb.y -= 16;
            break;
            default:
            break;
            }
        }
    }

    // block collision with walls
    for (int i = 0; i < L1_WALL_COUNT; i++) {
        for (int j = 0; j < L1_BLOCK_COUNT; j++) {
            if (aabb_is_overlapping(s->block[j].aabb, s->wall[i].aabb)) {
            s->block[j].aabb = aabb_resolve_collision(
                s->block[j].aabb, 
                s->player.direction,
                s->wall[i].aabb
            );

            // Make sure to also push player back
            s->player.aabb = aabb_resolve_collision(
                s->player.aabb, 
                s->player.direction,
                s->block[j].aabb
            );
            }
        }
    }

    // block collision with other blocks
    for (int i = 0; i < L1_BLOCK_COUNT; i++) {
        for (int j = 0; j < L1_BLOCK_COUNT; j++) {
            if (i != j) {
                if (aabb_is_overlapping(s->block[j].aabb, s->block[i].aabb)) {
                    s->block[j].aabb = aabb_resolve_collision(
                    s->block[j].aabb, 
                    s->player.direction,
                    s->block[i].aabb
                    );

                    // Make sure to also push player back
                    s->player.aabb = aabb_resolve_collision(
                    s->player.aabb, 
                    s->player.direction,
                    s->block[j].aabb
                    );
                }
            }
        }
    }

    // block collision with buttons
    for (int i = 0; i < L1_BLOCK_COUNT; i++) {
        for (int j = 0; j < L1_BLOCK_COUNT; j++) {
            if (aabb_is_overlapping(s->block[i].aabb, s->button[j].aabb)) {
                s->block[i].is_pressing_button = true;
                j = L1_BLOCK_COUNT; // Break out of the inner loop
            } else {
                s->block[i].is_pressing_button = false;
            }
        }
    }

    // Return to main menu if level is finished.
    for (int i = 0; i < L1_BLOCK_COUNT; i++) {
        if (s->block[i].is_pressing_button == false) {
            s->level_is_complete = false;
        }
    }

    if (s->level_is_complete) {
        return SCENE_WIN;
    }
    return SCENE_LEVEL_2;
}

void
scene_l2_draw(scene_res_t* scene_res) {
    /* walls */
    for (int i = 0; i < L1_WALL_COUNT; i++) {
        wall_draw(&s->wall[i]);
    }

    /* button */
    for (int i = 0; i < L1_BLOCK_COUNT; i++) {
        button_draw(&s->button[i]);
    }

    /* block */
    for (int i = 0; i < L1_BLOCK_COUNT; i++) {
        block_draw(&s->block[i]);
    }

    /* player */
    player_draw(&s->player);

    /* instructions */
    hl_draw_text(scene_res->font, "Level 2", 16, 4, HL_GB3);
    hl_draw_text(scene_res->font, "Press X to reset", 16, 148, HL_GB3);
}

void
scene_l2_unload(scene_res_t* scene_res) {
    free(s);
}
