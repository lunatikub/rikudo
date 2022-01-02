#ifndef __RIKUDO_H__
#define __RIKUDO_H__

#include <stdint.h>
#include <stdbool.h>

/* Difficulty of the rikudo to solve. */
enum level {
  BEGINNER,
  EASY,
  MEDIUM,
  HARD,
  EVIL,
  XL
};

/* Link between 2 cells. */
struct link {
  uint8_t idx_1; /* index of the cell 1. */
  uint8_t idx_2; /* index of the cell 2. */
};

struct rikudo {
  uint8_t *grid;
  uint8_t nr;
  struct link *links;
  uint8_t nr_link;
};

struct rikudo* rikudo_create(const uint8_t *grid,
                             enum level lvl,
                             const struct link *links,
                             uint8_t nr_link);

void rikudo_destroy(struct rikudo *rikudo);

#endif /* !__RIKUDO_H__ */
