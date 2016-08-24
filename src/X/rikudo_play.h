#ifndef RIKUDO_PLAY_H_
# define RIKUDO_PLAY_H_

#include "rikudo.h"
#include "rikudo_grid.h"

void rikudo_play_init(rikudo_t *ri);

void rikudo_play_clean(rikudo_t *ri);

void rikudo_play(rikudo_t *ri,
                 grid_t   *grid);

#endif /* !RIKUDO_PLAY_H_ */
