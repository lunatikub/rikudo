#ifndef RIKUDO_POS_H_
# define RIKUDO_POS_H_

typedef struct pos {
    int8_t x;
    int8_t y;
} pos_t;

static inline int rikudo_pos_cmp(pos_t *a, pos_t *b)
{
    return !(a->x == b->x && a->y == b->y);
}

#endif /* !RIKUDO_POS_H_ */
