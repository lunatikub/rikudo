#include <stdlib.h>

#include "rikudo.h"
#include "pretty_print.h"
#include "opts.h"

static const uint8_t grid[] = {
  0,  0, 0, 1,  0, 0, 0, 0, 0,  17, 22, 36,
  0,  0, 0, 0,  3, 0, 0, 0, 12, 0,  0,  0,
  20, 0, 0, 34, 0, 0, 0, 0, 0,  28, 7,  0
};

static const uint8_t expected[] = {
  15, 16, 23, 1,  2,  4,  5,  11, 14, 17, 22, 36,
  24, 25, 26, 27, 3, 6, 9,  10, 12, 13, 18, 19,
  20, 21, 35, 34, 33, 32, 31, 30, 29, 28, 7, 8
};

static const uint8_t nr_link = 5;
static const struct link links[] = {
  {6, 7}, {23, 24}, {16, 15}, {20, 19}, {18, 7},
};

int main(int argc, char **argv)
{
  if (parse_options(argc, argv) == false) {
    return 1;
  }
  pretty_print_init();
  struct rikudo *rikudo = rikudo_create(grid, BEGINNER, links, nr_link);

  uint8_t *solution = rikudo_solve(rikudo);

  #include <stdio.h>
  printf("expected\n");
  for (unsigned i = 0; i < rikudo->nr; ++i) {
    printf("%u ", expected[i]);
  }
  printf("\nsolution\n");
  for (unsigned i = 0; i < rikudo->nr; ++i) {
    printf("%u ", solution[i]);
  }
  printf("\n");

  if (solution != NULL) {
    free(solution);
  }
  rikudo_destroy(rikudo);
  pretty_print_exit();
  return 0;
}
