#include <stdlib.h>

#include "rikudo.h"
#include "pretty_print.h"
#include "opts.h"

static const uint8_t grid[] = {
  0, 16, 54, 0, 0, 0, 1, 0, 0,  0, 13, 0, 0, 60, 0, 36, 0,  0, 0,  0,
  0, 0,  0,  0, 0, 0, 0, 0, 45, 0, 0,  0, 0, 0,  0, 21, 0,  0, 26, 0,
  0, 0,  6,  0, 0, 0, 0, 0, 49, 0, 0,  0, 0, 0,  0, 39, 32, 0, 0,  0};
static const uint8_t nr_link = 8;
static const struct link links[] = {
  {43, 23}, {11, 26}, {22, 23}, {41, 40},
  {4, 14},  {20, 19}, {50, 49}, {16, 34},
};

int main(int argc, char **argv)
{
  if (parse_options(argc, argv) == false) {
    return 1;
  }
  pretty_print_init();
  struct rikudo *rikudo = rikudo_create(grid, EASY, links, nr_link);

  uint8_t *solution = rikudo_solve(rikudo);

  if (solution != NULL) {
    free(solution);
  }
  rikudo_destroy(rikudo);
  pretty_print_exit();
  return 0;
}
