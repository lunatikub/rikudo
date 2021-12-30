#ifndef __PRETTY_PRINT_H__
#define __PRETTY_PRINT_H__

#include "rikudo.h"

struct pretty_print_ctx {
  int row;
  int col;
};

struct pretty_print_ctx* pretty_print_init(void);

void pretty_print_exit(struct pretty_print_ctx *ctx);

void pretty_print_refresh(const struct rikudo *rikudo,
                          const struct pretty_print_ctx *ctx);

#endif /* !__PRETTY_PRINT_H__ */
