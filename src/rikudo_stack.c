#include <stdlib.h>

#include "rikudo_stack.h"

static inline entry_t* rikudo_stack_entry_new(grid_t *grid,
                                              int8_t  val,
                                              pos_t   pos)
{
    entry_t *new = NULL;

    new = malloc(sizeof(*new));
    new->grid = grid;
    new->val = val;
    new->pos = pos;

    return new;
}

void rikudo_stack_init(stack_t *st)
{
    TAILQ_INIT(&st->entries);
    st->nr = 0;
}

void rikudo_stack_push(stack_t *st,
                       grid_t  *grid,
                       int8_t   val,
                       pos_t    pos)
{
    entry_t *new = NULL;

    new = rikudo_stack_entry_new(grid, val, pos);
    TAILQ_INSERT_TAIL(&st->entries, new, entry);
    ++st->nr;
}

entry_t* rikudo_stack_pop(stack_t *st)
{
    entry_t *last = NULL;

    last = TAILQ_LAST(&st->entries, head_entries);
    TAILQ_REMOVE(&st->entries, last, entry);
    --st->nr;

    return last;
}

int rikudo_stack_is_empty(stack_t *st)
{
    return (st->nr == 0);
}

void rikudo_stack_free(entry_t *entry)
{
    rikudo_grid_free(entry->grid);
    free(entry);
}
