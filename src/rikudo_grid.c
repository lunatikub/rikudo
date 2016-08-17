#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <curses.h>

#include "rikudo_grid.h"

grid_t* rikudo_grid_new(uint32_t h,
                        uint32_t w)
{
    grid_t *new = malloc(sizeof(*new));

    new->g = malloc(h * w * sizeof(int8_t));
    new->s = malloc(h * w * sizeof(int8_t));

    memset(new->g, 0, h * w * sizeof(int8_t));
    memset(new->s, 0, h * w * sizeof(int8_t));

    return new;
}

grid_t* rikudo_grid_duplicate(grid_t   *grid,
                              uint32_t  h,
                              uint32_t  w)
{
    grid_t *dup = NULL;

    dup = rikudo_grid_new(h, w);

    memcpy(dup->g, grid->g, h * w);
    memcpy(dup->s, grid->s, h * w);

    return dup;
}

void rikudo_grid_free(grid_t *grid)
{
    free(grid->g);
    free(grid->s);
    free(grid);
}
