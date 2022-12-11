#ifndef ENTITIES_H
#define ENTITIES_H

#include "components.h"

/*
 * PLAYER
 */

typedef struct {
    direction_t direction;
    aabb_t aabb;
} player_t;

player_t player_new(int x, int y);
void player_move(player_t* player);
void player_draw(player_t* player);

/*
 * WALL
 */

typedef struct {
    aabb_t aabb;
} wall_t;

wall_t wall_new(int x, int y, int w, int h);
void wall_draw(wall_t* wall);

/*
 * BLOCK
 */

typedef struct {
    char isOnButton;
    direction_t direction;
    aabb_t aabb;
} block_t;

block_t block_new(int x, int y);
void block_draw(block_t* block);

/*
 * BUTTON
 */

typedef struct {
    aabb_t aabb;
} button_t;

button_t button_new(int x, int y);
void button_draw(button_t* button);

#endif