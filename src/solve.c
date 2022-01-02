#include <stdlib.h>
#include <string.h>

#include "solve.h"
#include "rikudo.h"
#include "neighbors.h"
#include "pretty_print.h"

#define NOT_FOUND (uint8_t)-1

static inline uint8_t neighbor_find(struct rikudo *rikudo,
                                    uint8_t idx, uint8_t val)
{
  FOREACH_NEIGHBOR(
    idx, rikudo->nr,
    if (rikudo->grid[neighbor] == val) {
      return neighbor;
    });
  return NOT_FOUND;
}

static inline bool rikudo_is_solution(struct solver *handle, uint8_t next_val)
{
  struct rikudo *rikudo = handle->rikudo;

  if (rikudo->nr == next_val) {
    handle->solution = calloc(rikudo->nr, sizeof(uint8_t));
    memcpy(handle->solution, rikudo->grid, rikudo->nr * sizeof(uint8_t));
    handle->solution_found = true;
    return true;
  }
  return false;
}

static bool rikudo_solve_backtracking(struct solver *handle, uint8_t idx, uint8_t val)
{
  struct rikudo *rikudo = handle->rikudo;
  uint8_t next_val = val + 1;
  uint8_t next_idx;

  /* A solution has been found, stop the recursion. */
  if (handle->solution_found == true) {
    return true;
  }

  /* Next value is a constant cell: has to be find in the neighborhood,
     otherwise it is an invalid grid. */
  if (handle->constant[next_val]) {
    if ((next_idx = neighbor_find(rikudo, idx, next_val)) == NOT_FOUND) {
      ++handle->failed;
      return false;
    }
    if (rikudo_is_solution(handle, next_val) == true) {
      return true;
    }
    if (rikudo_solve_backtracking(handle, next_idx, next_val) == false) {
      ++handle->failed;
      return false;
    }
  }

  /* Browse each empty neighbor and try to fill the next value */
  uint8_t nr = 0;
  FOREACH_NEIGHBOR(
    idx, rikudo->nr,
    if (rikudo->grid[neighbor] == 0) {
      ++nr;
      rikudo->grid[neighbor] = val + 1;
      if (rikudo_solve_backtracking(handle, neighbor, next_val) == false) {
        rikudo->grid[neighbor] = 0;
        --nr;
      }
    });

  handle->failed += nr != 0 ? 0 : 1;
  return nr != 0; /* almost 1 way has to be true */
}

static inline void constant_set(struct solver *handle)
{
  struct rikudo *rikudo = handle->rikudo;
  handle->constant = calloc(rikudo->nr + 1, sizeof(bool));

  for (uint8_t i = 0; i < rikudo->nr; ++i) {
    if (rikudo->grid[i] != 0) {
      handle->constant[rikudo->grid[i]] = true;
    }
  }
}

static inline void find_start_end(struct solver *handle)
{
  struct rikudo *rikudo = handle->rikudo;

  for (uint8_t i = 0; i < rikudo->nr; ++i) {
    if (rikudo->grid[i] == 1) {
      handle->start = i;
    } else if (rikudo->grid[i] == rikudo->nr) {
      handle->end = i;
    }
  }
}

uint8_t* rikudo_solve(struct rikudo *rikudo)
{
  struct solver handle = {
    .rikudo = rikudo,
    .failed = 0,
    .solution_found = false,
  };

  constant_set(&handle);
  find_start_end(&handle);

  rikudo_solve_backtracking(&handle, handle.start, 1);
  pretty_print_solution(&handle);

  free(handle.constant);

  if (handle.solution_found == true) {
    return handle.solution;
  }
  return NULL;
}
