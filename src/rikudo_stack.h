#ifndef RIKUDO_STACK_H_
# define RIKUDO_STACK_H_

#include <sys/queue.h>

#include "rikudo_grid.h"
#include "rikudo_pos.h"

typedef struct entry {
    TAILQ_ENTRY(entry) entry;
    grid_t *grid;
    int8_t  val;
    pos_t   pos;
} entry_t;

typedef struct stack {
    TAILQ_HEAD(head_entries, entry) entries;
    uint32_t nr;
} stack_t;

void rikudo_stack_init(stack_t *st);

void rikudo_stack_push(stack_t *st,
                       grid_t  *grid,
                       int8_t   val,
                       pos_t    pos);

entry_t* rikudo_stack_pop(stack_t *st);

int rikudo_stack_is_empty(stack_t *st);

void rikudo_stack_free(entry_t *entry);

#endif /* !RIKUDO_STACK_H_ */
