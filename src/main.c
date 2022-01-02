#include "rikudo.h"
#include "pretty_print.h"

/* static const uint8_t grid[] = { */
/*   0, 0,  0, 0, 0, 14, 0,  18, 0, 27, 0, 0, */
/*   0, 0,  0, 5, 0, 3,  0,  21, 0, 0,  0, 0, */
/*   0, 31, 0, 0, 0, 36, 10, 0,  0, 0,  0, 1 */
/* }; */

/* /\* static const uint8_t grid[] = { *\/ */
/* /\*     15, 16, 29, 12, 13, 14, 19, 18, 17, 27, 28, 30, 34, 11, 9, 5, 4, 3, *\/ */
/* /\*     20, 21, 22, 23, 24, 25, 26, 31, 32, 33, 35, 36, 10, 8,  7, 6, 2, 1}; *\/ */

/* static const uint8_t nr_link = 6; */

/* static const struct link links[] = { */
/*     {11, 2}, {24, 23}, {22, 21}, {21, 20}, {10, 2}, {1, 0}, */
/* }; */

static const uint8_t grid[] = {
  0,0,26,0,1,0,10,6,0,0,0,33,0,0,0,0,15,0,0,0,0,0,0,0,31,36,0,0,0,0,21,18,0,0,0,0};
/* static const uint8_t solution[] = {3,27,26,25,1,2,10,6,4,28,32,33,24,20,19,16,15,11,9,8,7,5,29,30,31,36,35,34,23,22,21,18,17,14,13,12}; */
static const uint8_t nr_link = 4;
static const struct link links[] = {{ 26, 27 }, { 13, 14 }, { 18, 19 }, { 33, 34 }, };

int main()
{
  pretty_print_init();
  struct rikudo *rikudo = rikudo_create(grid, BEGINNER, links, nr_link);

  rikudo_solve(rikudo);

  rikudo_destroy(rikudo);
  pretty_print_exit();
  return 0;
}
