#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rikudo.h"
#include "rikudo_read.h"
#include "rikudo_macro.h"

static inline void rikudo_grid_set_read(rikudo_t *ri,
                                        uint32_t  x,
                                        uint32_t  y)
{
    switch (GGET(ri->grid, x, y, ri->w)) {
        case X:
        case FREE:
        case ROOT:
            SSET(ri->grid, x, y, ri->w, GGET(ri->grid, x, y, ri->w));
            GSET(ri->grid, x, y, ri->w, 0);
            break;
        default:
            if (GGET(ri->grid, x, y, ri->w) == ri->end) {
                ri->end_pos.x = x;
                ri->end_pos.y = y;
            } else if (GGET(ri->grid, x, y, ri->w) == ri->start) {
                ri->start_pos.x = x;
                ri->start_pos.y = y;
            }
            SSET(ri->grid, x, y, ri->w, CONST);
            break;
    }
}

static inline void rikudo_trans_read(rikudo_t *ri,
                                     FILE     *f)
{
    uint32_t i = 0;

    for (i = 0; i < ri->nr_t; ++i) {
        fscanf(f, "(%hhd,%hhd)(%hhd,%hhd)\n",
               &ri->src_t[i].x, &ri->src_t[i].y,
               &ri->dst_t[i].x, &ri->dst_t[i].y);
    }
}

static inline void rikudo_grid_read(rikudo_t *ri,
                                    FILE     *f)
{
    int8_t x = 0;
    int8_t y = 0;

    for (y = 0; y < ri->h; ++y) {
        for (x = 0; x < ri->w; ++x) {
            fscanf(f, "%hhd", &GGET(ri->grid, x, y, ri->w));
            rikudo_grid_set_read(ri, x, y);
        }
        fscanf(f, "\n");
    }
}

static inline void rikudo_trans_alloc(rikudo_t *ri)
{
    ri->src_t = malloc(ri->nr_t * sizeof(pos_t));
    ri->dst_t = malloc(ri->nr_t * sizeof(pos_t));

    memset(ri->src_t, 0, ri->nr_t * sizeof(pos_t));
    memset(ri->dst_t, 0, ri->nr_t * sizeof(pos_t));
}

void rikudo_read_from_file(rikudo_t   *ri,
                           const char *filename)
{
    FILE *f = fopen(filename, "r");

    fscanf(f, "%hhd %hhd %hhd %hhd %u\n", &ri->h, &ri->w, &ri->start, &ri->end, &ri->nr_t);

    ri->grid = rikudo_grid_new(ri->h, ri->w);
    rikudo_trans_alloc(ri);

    rikudo_grid_read(ri, f);
    rikudo_trans_read(ri, f);

    fclose(f);
}
