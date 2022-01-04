#include <stdio.h>
#include <stdlib.h>

#include "rikudo.h"
#include "pretty_print.h"
#include "opts.h"
#include "parser.h"


static struct rikudo* rikudo_parse(void)
{
#define MAX 126
  enum level lvl = opt_get_level();
  uint8_t nr_link = opt_get_nr_link();
  uint8_t nr;
  uint8_t grid[MAX];
  struct link links[MAX];

  if (level_parse(lvl, &nr) == false) {
    return NULL;
  }
  if (nr >= MAX) {
    return NULL;
  }
  if (grid_parse(opt_get_grid(), grid, nr) == false) {
    return NULL;
  }
  if (links_parse(opt_get_links(), links, nr_link) == false) {
    return NULL;
  }

  return rikudo_create(grid, nr, links, nr_link);
#undef MAX
}

int main(int argc, char **argv)
{
  if (options_parse(argc, argv) == false) {
    return -1;
  }
  pretty_print_init();

  struct rikudo *rikudo = rikudo_parse();
  if (rikudo == NULL) {
    return -1;
  }

  uint8_t *solution = rikudo_solve(rikudo);
  if (solution != NULL) {
    free(solution);
  }

  rikudo_destroy(rikudo);
  options_clean();
  pretty_print_exit();

  return 0;
}
