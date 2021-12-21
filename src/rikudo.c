#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <rikudo.h>

static void set_start_end(struct rikudo *rikudo)
{
  for (uint8_t i = 0; i < rikudo->nr; ++i) {
    if (rikudo->grid[i] == 1) {
      rikudo->start = i;
    } else if (rikudo->grid[i] == rikudo->nr) {
      rikudo->end = i;
    }
  }
  assert(rikudo->start != 0 && rikudo->end != 0);
}

static const uint8_t nr_from_level[] = {
  [BEGINNER] = 36,
  [EASY] = 60,
  [MEDIUM] = 60,
  [HARD] = 90,
  [EVIL] = 90,
  [XL] = 126,
};

struct rikudo* rikudo_create(const uint8_t *grid,
                             enum level lvl,
                             const struct link *links,
                             uint8_t nr_link)
{
  struct rikudo *rikudo = calloc(1, sizeof(*rikudo));

  rikudo->lvl = lvl;
  rikudo->nr = nr_from_level[lvl];
  rikudo->nr_link = nr_link;

  rikudo->grid = calloc(rikudo->nr, sizeof(uint8_t));
  memcpy(rikudo->grid, grid, sizeof(uint8_t) * rikudo->nr);

  rikudo->links = calloc(nr_link, sizeof(struct link));
  memcpy(rikudo->links, links, sizeof(struct link) * nr_link);

  set_start_end(rikudo);

  return rikudo;
}

void rikudo_destroy(struct rikudo *rikudo)
{
  free(rikudo->grid);
  free(rikudo->links);
  free(rikudo);
}
