#include <stdlib.h>

#include "rikudo.h"
#include "pretty_print.h"
#include "opts.h"

static const uint8_t grid[] = {
  0,0,26,0,1,0,10,6,0,0,0,33,0,0,0,0,15,0,0,0,0,0,0,0,31,36,0,0,0,0,21,18,0,0,0,0};
static const uint8_t nr_link = 4;
static const struct link links[] = {{ 26, 27 }, { 13, 14 }, { 18, 19 }, { 33, 34 }, };

int main(int argc, char **argv)
{
  if (parse_options(argc, argv) == false) {
    return 1;
  }
  pretty_print_init();
  struct rikudo *rikudo = rikudo_create(grid, BEGINNER, links, nr_link);

  uint8_t *solution = rikudo_solve(rikudo);

  if (solution != NULL) {
    free(solution);
  }
  rikudo_destroy(rikudo);
  pretty_print_exit();
  return 0;
}
