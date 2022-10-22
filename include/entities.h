#ifndef ENTITIES_H
#define ENTITIES_H

#include "components.h"

typedef struct {
        int x;
        int y;
        direction_t direction;
        aabb_t aabb;
} player_t;

player_t player_new(int x, int y);
void player_move(player_t* player);
void player_resolve_collision(player_t* player, aabb_t* a);
void player_draw(player_t* player);

typedef struct {
        aabb_t aabb;
} wall_t;

wall_t wall_new(int x, int y, int w, int h);
void wall_draw(wall_t* wall);

#endif