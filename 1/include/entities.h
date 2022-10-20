#ifndef ENTITIES_H
#define ENTITIES_H

typedef struct {
        int x;
        int y;
} player_t;

player_t player_new(int x, int y);
void player_move(player_t* player);
void player_draw(player_t* player);

#endif