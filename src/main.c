#include "rikudo.h"
#include "pretty_print.h"

static const uint8_t grid[] = {
  0, 0,  0, 0, 0, 14, 0,  18, 0, 27, 0, 0,
  0, 0,  0, 5, 0, 3,  0,  21, 0, 0,  0, 0,
  0, 31, 0, 0, 0, 36, 10, 0,  0, 0,  0, 1
};

/* static const uint8_t solution[] = { */
/*     15, 16, 29, 12, 13, 14, 19, 18, 17, 27, 28, 30, 34, 11, 9, 5, 4, 3, */
/*     20, 21, 22, 23, 24, 25, 26, 31, 32, 33, 35, 36, 10, 8,  7, 6, 2, 1}; */

static const uint8_t nr_link = 6;

static const struct link links[] = {
    {11, 2}, {24, 23}, {22, 21}, {21, 20}, {10, 2}, {1, 0},
};

int main()
{
  struct pretty_print_ctx *pp_ctx = pretty_print_init();
  struct rikudo *rikudo = rikudo_create(grid, BEGINNER, links, nr_link);

  pretty_print_refresh(rikudo, pp_ctx);

  pretty_print_exit(pp_ctx);
  rikudo_destroy(rikudo);
  return 0;
}
