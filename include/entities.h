#ifndef ENTITIES_H
#define ENTITIES_H

#include "components.h"

typedef struct {
        direction_t direction;
        aabb_t aabb;
} player_t;

player_t player_new(int x, int y);
void player_move(player_t* player);
void player_draw(player_t* player);

typedef struct {
        aabb_t aabb;
} wall_t;

wall_t wall_new(int x, int y, int w, int h);
void wall_draw(wall_t* wall);

typedef struct {
        direction_t direction;
        aabb_t aabb;
} block_t;

block_t block_new(int x, int y);
void block_draw(block_t* block);

#endif