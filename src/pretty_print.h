#ifndef __PRETTY_PRINT_H__
#define __PRETTY_PRINT_H__

#include "rikudo.h"
#include "solve.h"

void pretty_print_init(void);

void pretty_print_exit(void);

void pretty_print_refresh(const struct solver *handle, uint8_t idx, uint8_t val);

void pretty_print_solution(const struct solver *handle);

#endif /* !__PRETTY_PRINT_H__ */
