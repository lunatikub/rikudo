#ifndef __NEIGHBORS_H__
#define __NEIGHBORS_H__

/**
 *  0 1
 * 5 X 2
 *  4 3
 **/
#define NR_NEIGHBOR 6

/**
 * Index of a cell give the list of the
 * neighbors in the linearized grid.
 *
 *                   125   90   91   92   93   94   95
 *                124    89   60   61   62   63   64   96
 *             123    88   59   36   37   38   39   65   97
 *          122    87    58   35   18   19   20   40   66   98
 *       121    86    57   34   17    6    7   21   41   67    99
 *    120    85    56    33   16    5    0    8   22   42   68   100
 * 119    84    55    32   15    4   XX    1    9   23   43    69   101
 *    118    83    54    31   14    3    2   10   24   44   70   102
 *       117    82    53   30   13   12   11   25   45   71   103
 *          116    81    52   29   28   27   26   46   72  104
 *             115    80   51   50   49   48   47   73  105
 *                114    79   78   77   76   75   74  106
 *                   113  112  111  110  109  108  107
 *
 */
static const uint8_t neighbors[][NR_NEIGHBOR] = {

  /* circle 1 */
  /*   0 */ { 5, 6, 7, 8, 1, -1 },
  /*   1 */ { 0, 8, 9, 10, 2, -1 },
  /*   2 */ { 3, 1, 10, 11, 12, -1 },
  /*   3 */ { 14, 4, 2, 12, 13, -1 },
  /*   4 */ { 15, 16, 5, 3, 14, -1 },
  /*   5 */ { 16, 17, 6, 0, 4, -1 },

  /* circle 2 */
  /*   6 */ { 17, 18, 19, 7, 0, 5 },
  /*   7 */ { 6, 19, 20, 21, 8, 0 },
  /*   8 */ { 0, 7, 21, 22, 9, 1 },
  /*   9 */ { 1, 8, 22, 23, 24, 10 },
  /*  10 */ { 2, 1, 9, 24, 25, 11 },
  /*  11 */ { 12, 2, 10, 25, 26, 27 },
  /*  12 */ { 13, 3, 2, 11, 27, 28 },
  /*  13 */ { 30, 14, 3, 12, 28, 29 },
  /*  14 */ { 31, 15, 4, 3, 13, 30 },
  /*  15 */ { 32, 33, 16, 4, 14, 31 },
  /*  16 */ { 33, 34, 17, 5, 4, 15 },
  /*  17 */ { 34, 35, 18, 6, 5, 16 },

  /* circle 3 */
  /*  18 */ { 35, 36, 37, 19, 6, 17 },
  /*  19 */ { 18, 37, 38, 20, 7, 6 },
  /*  20 */ { 19, 38, 39, 40, 21, 7 },
  /*  21 */ { 7, 20, 40, 41, 22, 8 },
  /*  22 */ { 8, 21, 41, 42, 23, 9 },
  /*  23 */ { 9, 22, 42, 43, 44, 24 },
  /*  24 */ { 10, 9, 23, 44, 45, 25 },
  /*  25 */ { 11, 10, 24, 45, 46, 26 },
  /*  26 */ { 27, 11, 25, 46, 47, 48 },
  /*  27 */ { 28, 12, 11, 26, 48, 49 },
  /*  28 */ { 29, 13, 12, 27, 49, 50 },
  /*  29 */ { 52, 30, 13, 28, 50, 51 },
  /*  30 */ { 53, 31, 14, 13, 29, 52 },
  /*  31 */ { 54, 32, 15, 14, 30, 53 },
  /*  32 */ { 55, 56, 33, 15, 31, 54 },
  /*  33 */ { 56, 57, 34, 16, 15, 32 },
  /*  34 */ { 57, 58, 35, 17, 16, 33 },
  /*  35 */ { 58, 59, 36, 18, 17, 34 },
};

#define FOREACH_NEIGHBOR(IDX, NR, CODE)                 \
  do {                                                  \
    for (unsigned N = 0; N < NR_NEIGHBOR; ++N) {        \
      uint8_t neighbor = neighbors[IDX][N];             \
      if (neighbor != -1 && neighbor < NR) {            \
        CODE;                                           \
      }                                                 \
    }                                                   \
  } while(0)

#endif /* !__NEIGHBORS_H__ */
