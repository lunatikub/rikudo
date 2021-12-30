#ifndef __RIKUDO_H__
#define __RIKUDO_H__

#include <stdint.h>
#include <stdbool.h>

enum level {
  BEGINNER,
  EASY,
  MEDIUM,
  HARD,
  EVIL,
  XL
};

struct link {
  uint8_t idx_1;
  uint8_t idx_2;
};

struct rikudo {
  uint8_t *grid;
  bool *to_fill;
  struct link *links;
  enum level lvl;
  uint8_t nr;
  uint8_t nr_link;
  uint8_t start;
  uint8_t end;
};

struct rikudo* rikudo_create(const uint8_t *grid,
                             enum level lvl,
                             const struct link *links,
                             uint8_t nr_link);

void rikudo_destroy(struct rikudo *rikudo);

#endif /* !__RIKUDO_H__ */
