#include <stdlib.h>

#include "rikudo_ia.h"
#include "rikudo_macro.h"

static inline int rikudo_const_cmp(const void *a,
                                   const void *b)
{
    const const_t*_a = (const const_t*)a;
    const const_t*_b = (const const_t*)b;

    return ((_a->val > _b->val) ? 1 : ((_a->val < _b->val) ? -1 : 0));
}

void rikudo_const_list_create(rikudo_t *ri)
{
    int8_t x      = 0;
    int8_t y      = 0;

    ri->lconst = malloc(ri->w * ri->h * sizeof(const_t));
    ri->nr_const = 0;

    for (y = 0; y < ri->h; ++y) {
        for (x = 0; x < ri->w; ++x) {
            if (SGET(ri->grid, x, y, ri->w) == CONST) {
                ri->lconst[ri->nr_const].val = GGET(ri->grid, x, y, ri->w);
                ri->lconst[ri->nr_const].pos.x = x;
                ri->lconst[ri->nr_const++].pos.y = y;
            }
        }
    }

    qsort(ri->lconst, ri->nr_const, sizeof(const_t), rikudo_const_cmp);
}

void rikudo_intuition(rikudo_t *ri)
{
    (void)ri;
}

uint8_t rikudo_trans_check(rikudo_t *ri,
                           grid_t   *grid)
{
    uint8_t n = 0;

    for (n = 0; n < ri->nr_t; ++n) {

        if (SGET(grid, ri->src_t[n].x, ri->src_t[n].y, ri->w) == FREE &&
            GGET(grid, ri->src_t[n].x, ri->src_t[n].y, ri->w) != 0 &&
            SGET(grid, ri->dst_t[n].x, ri->dst_t[n].y, ri->w) == FREE &&
            GGET(grid, ri->dst_t[n].x, ri->dst_t[n].y, ri->w) != 0) {

            int8_t diff = GGET(grid, ri->src_t[n].x, ri->src_t[n].y, ri->w) -
                GGET(grid, ri->dst_t[n].x, ri->dst_t[n].y, ri->w);

            if (diff != 1 && diff != -1) {
                return 1;
            }
        }
    }

    return 0;
}

int8_t rikudo_target_get(rikudo_t *ri,
                         int8_t    curr_val,
                         pos_t    *target_pos)
{
    int8_t target = 0;

    while (ri->lconst[target].val < curr_val) {
        ++target;
    }

    target_pos->x = ri->lconst[target].pos.x;
    target_pos->y = ri->lconst[target].pos.y;

    return ri->lconst[target].val;
}

int rikudo_next_const_is_connected(grid_t *grid,
                                   pos_t  *curr_pos,
                                   pos_t  *target_pos,
                                   int8_t  target,
                                   int8_t  h,
                                   int8_t  w)
{
    pos_t dst_pos;

    (void)target_pos;

    if ((L_SGET(grid, curr_pos->x, curr_pos->y, dst_pos.x, dst_pos.y, h, w) == CONST &&
         L_GGET(grid, curr_pos->x, curr_pos->y, dst_pos.x, dst_pos.y, h, w) == target)  ||
        (UL_SGET(grid, curr_pos->x, curr_pos->y, dst_pos.x, dst_pos.y, h, w) == CONST &&
         UL_GGET(grid, curr_pos->x, curr_pos->y, dst_pos.x, dst_pos.y, h, w) == target) ||
        (UR_SGET(grid, curr_pos->x, curr_pos->y, dst_pos.x, dst_pos.y, h, w) == CONST &&
         UR_GGET(grid, curr_pos->x, curr_pos->y, dst_pos.x, dst_pos.y, h, w) == target) ||
        (R_SGET(grid, curr_pos->x, curr_pos->y, dst_pos.x, dst_pos.y, h, w) == CONST &&
         R_GGET(grid, curr_pos->x, curr_pos->y, dst_pos.x, dst_pos.y, h, w) == target)  ||
        (DL_SGET(grid, curr_pos->x, curr_pos->y, dst_pos.x, dst_pos.y, h, w) == CONST &&
        DL_GGET(grid, curr_pos->x, curr_pos->y, dst_pos.x, dst_pos.y, h, w) == target)  ||
        (DR_SGET(grid, curr_pos->x, curr_pos->y, dst_pos.x, dst_pos.y, h, w) == CONST &&
         DR_GGET(grid, curr_pos->x, curr_pos->y, dst_pos.x, dst_pos.y, h, w) == target)) {
            return 1;
    }

    return 0;
}

uint8_t rikudo_next_pos_get(grid_t *grid,
                            pos_t  *curr_pos,
                            pos_t  *next_pos,
                            int8_t  h,
                            int8_t  w)
{
    uint8_t n = 0;

    if (L_SGET(grid, curr_pos->x, curr_pos->y, next_pos[n].x, next_pos[n].y, h, w) == FREE &&
        L_GGET(grid, curr_pos->x, curr_pos->y, next_pos[n].x, next_pos[n].y, h, w) == 0) {
        ++n;
    }

    if (UL_SGET(grid, curr_pos->x, curr_pos->y, next_pos[n].x, next_pos[n].y, h, w) == FREE &&
        UL_GGET(grid, curr_pos->x, curr_pos->y, next_pos[n].x, next_pos[n].y, h, w) == 0) {
        ++n;
    }

    if (UR_SGET(grid, curr_pos->x, curr_pos->y, next_pos[n].x, next_pos[n].y, h, w) == FREE &&
        UR_GGET(grid, curr_pos->x, curr_pos->y, next_pos[n].x, next_pos[n].y, h, w) == 0) {
        ++n;
    }

    if (R_SGET(grid, curr_pos->x, curr_pos->y, next_pos[n].x, next_pos[n].y, h, w) == FREE &&
        R_GGET(grid, curr_pos->x, curr_pos->y, next_pos[n].x, next_pos[n].y, h, w) == 0) {
        ++n;
    }

    if (DL_SGET(grid, curr_pos->x, curr_pos->y, next_pos[n].x, next_pos[n].y, h, w) == FREE &&
        DL_GGET(grid, curr_pos->x, curr_pos->y, next_pos[n].x, next_pos[n].y, h, w) == 0) {
        ++n;
    }

    if (DR_SGET(grid, curr_pos->x, curr_pos->y, next_pos[n].x, next_pos[n].y, h, w) == FREE &&
        DR_GGET(grid, curr_pos->x, curr_pos->y, next_pos[n].x, next_pos[n].y, h, w) == 0) {
        ++n;
    }

    return n;
}
