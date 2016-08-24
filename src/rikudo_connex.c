#include <curses.h>
#include <stdlib.h>
#include <string.h>

#include "rikudo_connex.h"
#include "rikudo_grid.h"
#include "rikudo_macro.h"
#include "rikudo_cycle.h"

static uint8_t __Y = 0;

#define X_DBG     (140)
#define MAX_GROUP (20)

static inline void rikudo_group_dump(int8_t *a,
                                     int8_t  w,
                                     int8_t  h,
                                     int8_t *max,
                                     int8_t  nr_group,
                                     int8_t  min_max)
{
    int8_t i = 0;
    int8_t j = 0;

    __Y = 0;

    mvprintw(__Y++, X_DBG, "min_max:%d", min_max);

    for (i = 0; i < h; i++) {
        mvprintw(__Y, 4 + X_DBG + i * 3, "%2d ", i);
        mvprintw(__Y + 1, 4 + X_DBG + i * 3, "--");
    }
    __Y += 2;

    for (i = 0; i < h; i++) {
        mvprintw(__Y, X_DBG, "%2d |", i);
        for (j = 0; j < w; ++j) {
            mvprintw(__Y, X_DBG + 4 + j * 3, "%2d", a[i * w + j]);;
        }
        ++__Y;
    }

    ++__Y;

    for (i = 0; i < MAX_GROUP; ++i) {
        mvprintw(__Y + i, X_DBG, "%40s", " ");
    }

    for (i = 0; i < nr_group - 1; ++i) {
        mvprintw(__Y + i, X_DBG, "group:%2u, max:%2u", i + 1, max[i]);
    }
}

static inline int rikudo_free_member_find(rikudo_t *ri,
                                          int8_t   *gg,
                                          int8_t   *src_x,
                                          int8_t   *src_y)
{
    int8_t x = 0;
    int8_t y = 0;

    for (y = 0; y < ri->h; ++y) {
        for(x = 0; x < ri->w; ++x) {
            if (AGET(gg, x, y, ri->w) == 0) {
                *src_x = x;
                *src_y = y;
                return 1;
            }
        }
    }

    return 0;
}

static inline void rikudo_dfs_member_attach(rikudo_t *ri,
                                            grid_t   *grid,
                                            int8_t   *gg,
                                            uint8_t   group_id,
                                            int8_t    x,
                                            int8_t    y,
                                            int8_t   *max)

{
    int8_t dst_x;
    int8_t dst_y;

    ASET(gg, x, y, ri->w, group_id);

    if (L_AGET(gg, x, y, dst_x, dst_y, ri->h, ri->w) == 0) {
        rikudo_dfs_member_attach(ri, grid, gg, group_id, dst_x, dst_y, max);
    } else if (L_SGET(grid, x, y, dst_x, dst_y, ri->h, ri->w) == FREE ||
               L_SGET(grid, x, y, dst_x, dst_y, ri->h, ri->w) == CONST) {
        *max = (*max > L_GGET(grid, x, y, dst_x, dst_y, ri->h, ri->w)) ? *max :
            L_GGET(grid, x, y, dst_x, dst_y, ri->h, ri->w);
    }

    if (R_AGET(gg, x, y, dst_x, dst_y, ri->h, ri->w) == 0) {
        rikudo_dfs_member_attach(ri, grid, gg, group_id, dst_x, dst_y, max);
    } else if (R_SGET(grid, x, y, dst_x, dst_y, ri->h, ri->w) == FREE ||
               R_SGET(grid, x, y, dst_x, dst_y, ri->h, ri->w) == CONST) {
        *max = (*max > R_GGET(grid, x, y, dst_x, dst_y, ri->h, ri->w)) ? *max :
            R_GGET(grid, x, y, dst_x, dst_y, ri->h, ri->w);
    }

    if (DR_AGET(gg, x, y, dst_x, dst_y, ri->h, ri->w) == 0) {
        rikudo_dfs_member_attach(ri, grid, gg, group_id, dst_x, dst_y, max);
    } else if (DR_SGET(grid, x, y, dst_x, dst_y, ri->h, ri->w) == FREE ||
               DR_SGET(grid, x, y, dst_x, dst_y, ri->h, ri->w) == CONST) {
        *max = (*max > DR_GGET(grid, x, y, dst_x, dst_y, ri->h, ri->w)) ? *max :
            DR_GGET(grid, x, y, dst_x, dst_y, ri->h, ri->w);
    }

    if (DL_AGET(gg, x, y, dst_x, dst_y, ri->h, ri->w) == 0) {
        rikudo_dfs_member_attach(ri, grid, gg, group_id, dst_x, dst_y, max);
    } else if (DL_SGET(grid, x, y, dst_x, dst_y, ri->h, ri->w) == FREE ||
               DL_SGET(grid, x, y, dst_x, dst_y, ri->h, ri->w) == CONST) {
        *max = (*max > DL_GGET(grid, x, y, dst_x, dst_y, ri->h, ri->w)) ? *max :
            DL_GGET(grid, x, y, dst_x, dst_y, ri->h, ri->w);
    }

    if (UR_AGET(gg, x, y, dst_x, dst_y, ri->h, ri->w) == 0) {
        rikudo_dfs_member_attach(ri, grid, gg, group_id, dst_x, dst_y, max);
    } else if (UR_SGET(grid, x, y, dst_x, dst_y, ri->h, ri->w) == FREE ||
               UR_SGET(grid, x, y, dst_x, dst_y, ri->h, ri->w) == CONST) {
        *max = (*max > UR_GGET(grid, x, y, dst_x, dst_y, ri->h, ri->w)) ? *max :
            UR_GGET(grid, x, y, dst_x, dst_y, ri->h, ri->w);
    }

    if (UL_AGET(gg, x, y, dst_x, dst_y, ri->h, ri->w) == 0) {
        rikudo_dfs_member_attach(ri, grid, gg, group_id, dst_x, dst_y, max);
    } else if (UL_SGET(grid, x, y, dst_x, dst_y, ri->h, ri->w) == FREE ||
               UL_SGET(grid, x, y, dst_x, dst_y, ri->h, ri->w) == CONST) {
        *max = (*max > UL_GGET(grid, x, y, dst_x, dst_y, ri->h, ri->w)) ? *max :
            UL_GGET(grid, x, y, dst_x, dst_y, ri->h, ri->w);
    }
}

int8_t rikudo_connex(rikudo_t *ri,
                     grid_t   *grid)
{
    rikudo_cycle_start();

    int8_t x = 0;
    int8_t y = 0;

    int8_t *gg = malloc(ri->w * ri->h);

    memset(gg, 0, ri->w * ri->h);

    for (y = 0; y < ri->h; ++y) {
        for(x = 0; x < ri->w; ++x) {
            if (SGET(grid, x, y, ri->w) == FREE && GGET(grid, x, y, ri->w) == 0) {
                ASET(gg, x, y, ri->w, 0);
            } else {
                ASET(gg, x, y, ri->w, -1);
            }
        }
    }

    int8_t group_id = 1;
    int8_t max[MAX_GROUP] = { };
    int8_t min_max = 127;

    while (rikudo_free_member_find(ri, gg, &x, &y)) {
        rikudo_dfs_member_attach(ri, grid, gg, group_id, x, y, &max[group_id - 1]);
        if (max[group_id - 1] < min_max) {
            min_max = max[group_id - 1];
        }
        ++group_id;
    }

    rikudo_group_dump(gg, ri->w, ri->h, max, group_id, min_max);

    free(gg);
    rikudo_cycle_stop(RIKUDO_SUBSYS_CONNEX);
    return min_max;
}
