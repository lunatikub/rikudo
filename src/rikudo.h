#ifndef RIKUDO_H_
# define RIKUDO_H_

#include <X11/extensions/XTest.h>

#include "rikudo_grid.h"
#include "rikudo_stack.h"
#include "rikudo_pos.h"
#include "rikudo_cfg.h"
#include "rikudo_stat.h"

#define ROOT  (-2)
#define X     (-1)
#define FREE  (0)
#define CONST (1)

typedef struct {
    int8_t val;
    pos_t  pos;
} const_t;

typedef struct rikudo {
    grid_t   *grid;
    stack_t   st;
    /* Size of the grid */
    int8_t    h;
    int8_t    w;
    /* start and end position information */
    pos_t     start_pos;
    pos_t     end_pos;
    int8_t    start;
    int8_t    end;
    /* List of transitions */
    pos_t    *src_t;
    pos_t    *dst_t;
    uint32_t  nr_t;
    /* List of const cases */
    uint8_t   nr_const;
    const_t  *lconst;
    /* X11 */
    Display  *dpy;
    uint32_t  mx_root;
    uint32_t  my_root;
    /* stat */
    rikudo_stat_t stat;
} rikudo_t;

#endif /* !RIKUDO_H_ */
