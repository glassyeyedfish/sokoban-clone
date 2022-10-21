#ifndef COMPONENTS_H
#define COMPONENTS_H

typedef struct {
        int x;
        int y;
        int w;
        int h;
} aabb_t;

int aabb_is_overlapping(aabb_t* a, aabb_t* b);

#endif