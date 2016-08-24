#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "rikudo.h"
#include "rikudo_reverse.h"
#include "rikudo_cfg.h"

#include "rikudo_36.h"
#include "rikudo_60.h"

#define MAX_VAL (126)

static inline void rikudo_reverse_sz_set(rikudo_t *ri)
{
    switch (ri->end) {
        case 36:
            ri->h = 7;
            ri->w = 7;
            break;
        case 60:
            ri->h = 9;
            ri->w = 9;
            break;
    }
}

static inline void rikudo_trans_alloc(rikudo_t *ri)
{
    ri->src_t = malloc(ri->nr_t * sizeof(pos_t));
    ri->dst_t = malloc(ri->nr_t * sizeof(pos_t));

    memset(ri->src_t, 0, ri->nr_t * sizeof(pos_t));
    memset(ri->dst_t, 0, ri->nr_t * sizeof(pos_t));
}

static inline void rikudo_trans_reverse(rikudo_t   *ri,
                                        const char *trans,
                                        pos_t      *matrix)
{
    uint8_t src;
    uint8_t dst;
    char tmp[256];
    char *_src = NULL;
    char *_dst = NULL;
    char *iter = NULL;
    uint8_t n = 0;

    strcpy(tmp, trans);

    iter = strchr(tmp, '[');
    _src = iter + 1;
    iter = strchr(iter, ',');

    do {
        _dst = _src + 1;
        if (iter - _src == 5) {
            ++_dst;
        }
        *_dst = 0;

        sscanf(_src, "%hhd", &src);
        sscanf(_dst + 1, "%hhd,", &dst);

        if (n % 2 == 0) {
            ri->src_t[n / 2].x = matrix[src - 1].x;
            ri->src_t[n / 2].y = matrix[src - 1].y;
            ri->dst_t[n / 2].x = matrix[dst - 1].x;
            ri->dst_t[n / 2].y = matrix[dst - 1].y;
        }
        _src = iter + 1;
        ++n;
    } while ((iter = strchr(iter + 1, ',')));
}

static inline void rikudo_case_reverse_matrix(rikudo_t *ri,
                                              pos_t    *matrix,
                                              int8_t   *val)
{
    uint8_t n = 0;

    for (n = 0; n < ri->end; ++n) {
        ri->grid->g[(matrix[n].y * ri->w + matrix[n].x)] = val[n];
        if (val[n] == 0) {
            ri->grid->s[(matrix[n].y * ri->w + matrix[n].x)] = FREE;
        } else {
            if (val[n] == ri->start) {
                ri->start_pos.x = matrix[n].x;
                ri->start_pos.y = matrix[n].y;
            } else if (val[n] == ri->end) {
                ri->end_pos.x = matrix[n].x;
                ri->end_pos.y = matrix[n].y;
            }
            ri->grid->s[(matrix[n].y * ri->w + matrix[n].x)] = CONST;
        }
    }
}

static inline void rikudo_case_reverse_undefined(rikudo_t *ri,
                                                 pos_t    *undefined)
{
    uint8_t n = 0;

    for (n = 0; undefined[n].x != -1 ; ++n) {
        ri->grid->g[(undefined[n].y * ri->w + undefined[n].x)] = 0;
        ri->grid->s[(undefined[n].y * ri->w + undefined[n].x)] = X;
    }
}

static inline void rikudo_case_reverse_root(rikudo_t *ri,
                                            pos_t    *root)
{
    ri->grid->g[root->x + root->y * ri->w] = 0;
    ri->grid->s[root->x + root->y * ri->w] = ROOT;
}

static pos_t    *matrix = NULL;
static uint32_t  end    = 0;

void rikudo_reverse_from_html(rikudo_t   *ri,
                              const char *grid,
                              const char *nr_t,
                              const char *trans)
{
    int8_t val[MAX_VAL] = { };
    uint8_t nr_val = 0;
    pos_t *undefined = NULL;
    pos_t *root = NULL;
    const char *iter = grid;

    iter = strstr(iter, "[");

    do {
        sscanf(iter + 1, "%hhd,", &val[nr_val++]);
        ++iter;
    } while ((iter = strstr(iter, ",")));

    ri->start = 1;
    ri->end = nr_val;
    end = nr_val;
    rikudo_reverse_sz_set(ri);
    ri->grid = rikudo_grid_new(ri->h, ri->w);

    switch (ri->end) {
        case 36:
            matrix = matrix_36;
            undefined = undefined_36;
            root = &root_36;
            break;
        case 60:
            matrix = matrix_60;
            undefined = undefined_60;
            root = &root_60;
            break;
        default:
            fprintf(stderr, "rikudo_reverce.c(%u): matrix needed\n", __LINE__);
            abort();
    };

    rikudo_case_reverse_matrix(ri, matrix, val);
    rikudo_case_reverse_undefined(ri, undefined);
    rikudo_case_reverse_root(ri, root);
    sscanf(nr_t, "%d", &ri->nr_t);
    rikudo_trans_alloc(ri);
    rikudo_trans_reverse(ri, trans, matrix);
}

#ifdef RIKUDO_CFG_DUMP

void rikudo_reverse_dump_to_html(rikudo_t *ri,
                                 grid_t   *grid)
{
    uint8_t i = 0;

    printf("[");
    for (i = 0; i < end; ++i) {
        printf("%i",  grid->g[matrix[i].x + matrix[i].y * ri->w]);
        if (i != end -1 ) {
            printf(",");
        }
    }
    printf("]");
}

#else

void rikudo_reverse_dump_to_html(rikudo_t *ri,
                                 grid_t   *grid)
{
    (void)ri;
    (void)grid;
}

#endif
