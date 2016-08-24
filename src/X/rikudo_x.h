#ifndef RIKUDO_X_H_
# define RIKUDO_X_H_

#include "rikudo_grid.h"
#include "rikudo_stack.h"
#include "rikudo.h"

void rikudo_x_init(void);
void rikudo_x_clean(void);
void rikudo_x_pause(void);

void rikudo_dump(rikudo_t   *ri,
                 grid_t     *grid);

void rikudo_wait(uint32_t n);

#endif /* !RIKUDO_X_H_ */
