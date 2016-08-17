#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "rikudo.h"
#include "rikudo_grid.h"
#include "rikudo_stack.h"
#include "rikudo_x.h"
#include "rikudo_read.h"
#include "rikudo_macro.h"
#include "rikudo_ia.h"
#include "rikudo_reverse.h"
#include "rikudo_play.h"

#define RIKUDO_MAX_POS (6)

/* #define N_THREAD (8) */
/* static pthread_mutex_t st_mutex; */
/* static uint8_t win = 0; */

static inline void rikudo_init(rikudo_t *ri)
{
    memset(ri, 0, sizeof(rikudo_t));
    rikudo_stack_init(&ri->st);
    rikudo_x_init();
    rikudo_play_init(ri);
}

static inline void rikudo_clean(rikudo_t *ri)
{
    rikudo_grid_free(ri->grid);
    rikudo_x_clean();
    rikudo_play_clean(ri);
}

static inline int rikudo_free_play(rikudo_t *ri,
                                   grid_t   *curr_grid,
                                   pos_t    *curr_pos,
                                   int8_t    curr_val)
{
    pos_t next_pos[RIKUDO_MAX_POS] = { };
    uint32_t  i        = 0;
    uint32_t  nr_pos   = 0;
    grid_t   *new_grid = NULL;

    nr_pos = rikudo_next_pos_get(curr_grid, curr_pos, next_pos, ri->h, ri->w);

    for (i = 0; i < nr_pos; ++i) {
        new_grid = rikudo_grid_duplicate(curr_grid, ri->h, ri->w);
        GSET(new_grid, next_pos[i].x, next_pos[i].y, ri->w, curr_val + 1);

        if (rikudo_trans_check(ri, curr_grid)) {
            rikudo_grid_free(new_grid);
            return 0;
        }

        rikudo_stack_push(&ri->st, new_grid, curr_val + 1, next_pos[i]);
        /* rikudo_dump(ri, new_grid); */
    }

    return 0;
}

static inline int rikudo_const_play(rikudo_t *ri,
                                    grid_t   *curr_grid,
                                    pos_t    *curr_pos,
                                    int8_t    curr_val,
                                    pos_t    *target_pos,
                                    int8_t    target_val)

{
    grid_t *new_grid = NULL;

    if (rikudo_next_const_is_connected(curr_grid, curr_pos, target_pos,
                                       target_val, ri->h, ri->w)) {

        if (target_val == ri->end) {
            if (rikudo_trans_check(ri, curr_grid)) {
                return 0;
            }
            rikudo_dump(ri, curr_grid);
            getchar();
            /* rikudo_play(ri, curr_grid); */
            return 1;
        }

        new_grid = rikudo_grid_duplicate(curr_grid, ri->h, ri->w);
        rikudo_stack_push(&ri->st, new_grid, curr_val + 1, *target_pos);

        /* rikudo_dump(ri, new_grid); */
    }

    return 0;
}

static inline int rikudo_do(rikudo_t *ri,
                            grid_t   *curr_grid,
                            pos_t    *curr_pos,
                            int8_t    curr_val)
{
    int8_t target_val = 0;
    pos_t  target_pos;

    target_val = rikudo_target_get(ri, curr_val, &target_pos);

    if (curr_val + 1 == target_val) {
        return rikudo_const_play(ri, curr_grid, curr_pos, curr_val, &target_pos, target_val);
    }

    return rikudo_free_play(ri, curr_grid, curr_pos, curr_val);
}

int main(int argc, char **argv)
{
    rikudo_t ri;
    entry_t *entry = NULL;

    rikudo_init(&ri);

    if (argc < 4) {
        return 1;
    }

    rikudo_reverse_from_html(&ri, argv[1], argv[2], argv[3]);

/* rikudo_read_from_file(&ri, argv[1]); */
    rikudo_const_list_create(&ri);
    rikudo_intuition(&ri);
    /* rikudo_dump(&ri, ri.grid); */

    rikudo_do(&ri, ri.grid, &ri.start_pos, 1);

    while (!rikudo_stack_is_empty(&ri.st)) {
        entry = rikudo_stack_pop(&ri.st);

        /* rikudo_dump(ri, entry->grid); */
        if (rikudo_do(&ri, entry->grid, &entry->pos, entry->val)) {
            rikudo_stack_free(entry);
            break;
        }
        rikudo_stack_free(entry);
    }

    /* pthread_t tid[N_THREAD]; */
    /* uint8_t i = 0; */

    /* for (i = 0; i < N_THREAD; ++i) { */
    /*     pthread_create(&tid[i], NULL, rikudo_thread, &ri); */
    /* } */

    /* for (i = 0; i < N_THREAD; ++i) { */
    /*     pthread_join(tid[i], NULL); */
    /* } */

    rikudo_clean(&ri);

    return 0;
}
