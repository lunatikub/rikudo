#include <stdio.h>
#include <stdlib.h>

#include "rikudo.h"
#include "pretty_print.h"
#include "opts.h"
#include "parser.h"


static struct rikudo* rikudo_parse(void)
{
  enum level lvl = opt_get_level();
  uint8_t nr;
#define MAX_NR_CELL 126
  uint8_t grid[MAX_NR_CELL];
#undef MAX_NR_CELL

  if (level_parse(lvl, &nr) == false) {
    return NULL;
  }

  if (grid_parse(opt_get_grid(), grid, nr) == false) {
    return NULL;
  }

  printf("level: %u\n", lvl);
  printf("nr:    %u\n", nr);
  printf("grid:  ");
  for (unsigned i = 0; i < nr; ++i) {
    printf("%u ", grid[i]);
  }
  printf("\n");

  return rikudo_create(grid, nr, NULL, 0);
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

  rikudo_destroy(rikudo);
  options_clean();
  pretty_print_exit();

  return 0;
}

/* uint8_t *solution = rikudo_solve(rikudo); */
/* if (solution != NULL) { */
/*   free(solution); */
/* } */
