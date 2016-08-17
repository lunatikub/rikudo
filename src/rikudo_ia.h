#ifndef RIKUDO_IA_H_
# define RIKUDO_IA_H_

#include "rikudo.h"

uint8_t rikudo_next_pos_get(grid_t *grid,
                            pos_t  *curr_pos,
                            pos_t  *next_pos,
                            int8_t  h,
                            int8_t  w);

int8_t rikudo_target_get(rikudo_t *ri,
                         int8_t    curr_val,
                         pos_t    *target_pos);

int rikudo_next_const_is_connected(grid_t *grid,
                                   pos_t  *curr_pos,
                                   pos_t  *target_pos,
                                   int8_t  target,
                                   int8_t  h,
                                   int8_t  w);

uint8_t rikudo_trans_check(rikudo_t *ri,
                           grid_t   *grid);

void rikudo_intuition(rikudo_t *ri);

void rikudo_const_list_create(rikudo_t *ri);

#endif /* !RIKUDO_IA_H_ */
