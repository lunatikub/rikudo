#ifndef __SOLVE_H__
#define __SOLVE_H__

#include <stdint.h>
#include <stdbool.h>

/**
 * Context for the solver.
 */
struct solver {
  struct rikudo *rikudo; /* rikudo to solve. */
  bool *constant; /* true if the value is a constant cell. */
  uint32_t failed; /* number of branch has been failed. */
  bool solution_found; /* true if a solution has been found. */
  uint8_t *solution; /* solution has been found. */
  uint8_t start; /* cell start index of value 1. */
  uint8_t end; /* cell end index of value 'nr'. */
};

/**
 * Solve a rikudo grid.
 * Return the solution found, otherwise return NULL.
 */
void rikudo_solve(struct rikudo *rikudo);

#endif /* !__SOLVE_H__ */
