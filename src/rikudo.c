#include <stdlib.h>
#include <string.h>

#include <rikudo.h>

struct rikudo* rikudo_create(const uint8_t *grid,
                             uint32_t nr,
                             const struct link *links,
                             uint8_t nr_link)
{
  struct rikudo *rikudo = calloc(1, sizeof(*rikudo));

  rikudo->nr_link = nr_link;
  rikudo->nr = nr;

  rikudo->grid = calloc(rikudo->nr, sizeof(uint8_t));
  memcpy(rikudo->grid, grid, sizeof(uint8_t) * rikudo->nr);

  rikudo->links = calloc(nr_link, sizeof(struct link));
  memcpy(rikudo->links, links, sizeof(struct link) * nr_link);

  return rikudo;
}

void rikudo_destroy(struct rikudo *rikudo)
{
  free(rikudo->grid);
  free(rikudo->links);
  free(rikudo);
}
