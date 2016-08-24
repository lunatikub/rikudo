#ifndef RIKUDO_STAT_H_
# define RIKUDO_STAT_H_

#include <stdint.h>

typedef struct {
    uint64_t  nr_grid;
} rikudo_stat_t;

void rikudo_stat_init(rikudo_stat_t *stat);

#define RIKUDO_STAT_INC_NR_GRID(stat) (++((stat)->nr_grid))

#endif /* !RIKUDO_STAT_H_ */
