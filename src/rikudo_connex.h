#ifndef RIKUDO_CONNEX_H_
# define RIKUDO_CONNEX_H_

#include <stdint.h>
#include <sys/queue.h>

#include "rikudo.h"
#include "rikudo_pos.h"

int8_t rikudo_connex(rikudo_t *ri,
                     grid_t   *grid);

#endif /* !RIKUDO_CONNEX_H_ */
