#ifndef RIKUDO_GRID_H_
# define RIKUDO_GRID_H_

#include <stdint.h>

typedef struct grid {
    int8_t   *g;
    int8_t   *s;
} grid_t;

grid_t* rikudo_grid_new(uint32_t h, uint32_t w);
grid_t* rikudo_grid_duplicate(grid_t *grid, uint32_t h, uint32_t w);
void rikudo_grid_free(grid_t *grid);

#endif /* !RIKUDO_GRID_H_ */
