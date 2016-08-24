#include <stdint.h>
#include <curses.h>
#include <unistd.h>

#include "rikudo_x.h"
#include "rikudo.h"
#include "rikudo_macro.h"

#ifdef RIKUDO_X

#define RED    (1)
#define ORANGE (2)
#define BLUE   (3)
#define YELLOW (4)

#define START_Y_DBG (1)
#define X_DBG (100)

static uint8_t __Y = 0;

void rikudo_x_init(void)
{
    initscr();
    start_color();

    init_pair(RED, COLOR_RED, COLOR_BLACK);
    init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);

    init_color(ORANGE, 1000, 640, 0);
    init_pair(ORANGE, ORANGE, COLOR_BLACK);
}

void rikudo_x_clean(void)
{
    endwin();
}

/* void rikudo_x_pause(void) */
/* { */
/*     refresh(); */
/*     /\* getchar(); *\/ */
/* } */

#define _X(_x) (5 * (_x) + (2 * (y % 2)))
#define _Y(_y) (4 * (_y))

static inline void rikudo_case_color_set(int8_t  v,
                                         uint8_t start_end)
{
    if (v == CONST) {
        if (start_end) {
            attron(COLOR_PAIR(RED));
        } else {
            attron(COLOR_PAIR(ORANGE));
        }
    }
}

static inline void rikudo_case_color_unset(int8_t  v,
                                           uint8_t start_end)
{
    if (v == CONST) {
        if (start_end) {
            attroff(COLOR_PAIR(RED));
        } else {
            attroff(COLOR_PAIR(ORANGE));
        }
    }
}

static inline void rikudo_case_dump(rikudo_t *ri,
                                    grid_t   *grid,
                                    int8_t    x,
                                    int8_t    y,
                                    int8_t    w)
{
    uint8_t start_end = 0;

    if ((ri->start_pos.x == x && ri->start_pos.y == y) ||
        (ri->end_pos.x == x && ri->end_pos.y == y)) {
        start_end = 1;
    }

    rikudo_case_color_set(SGET(grid, x, y, w), start_end);
    mvprintw(_Y(y) + 0, _X(x), " __");
    mvprintw(_Y(y) + 1, _X(x), "/  \\");
    if (SGET(grid, x, y, w) == ROOT) {
        mvprintw(_Y(y) + 2, _X(x), "|XX|");
    } else if (GGET(grid, x, y, w)) {
        mvprintw(_Y(y) + 2, _X(x), "|%2i|", GGET(grid, x, y, w));
    } else {
        mvprintw(_Y(y) + 2, _X(x), "|  |");
    }
    mvprintw(_Y(y) + 3, _X(x), "\\__/");
    rikudo_case_color_unset(SGET(grid, x, y, w), start_end);
}

static inline void rikudo_trans_dump(grid_t  *grid,
                                     pos_t   *src,
                                     pos_t   *dst,
                                     int8_t   w,
                                     uint8_t  nr_t)
{
    uint32_t i = 0;

    for (i = 0; i < nr_t; ++i) {
        int8_t v_src = GGET(grid, src[i].x, src[i].y, w);
        int8_t v_dst = GGET(grid, dst[i].x, dst[i].y, w);

        mvprintw(__Y, X_DBG, "(%2d,%2d) %2d <-- %2d --> %2d (%2d,%2d)",
                 src[i].x, src[i].y, v_src, v_src - v_dst,
                 v_dst, dst[i].x, dst[i].y);
        ++__Y;
    }
}

void rikudo_x_main_grid_dump(rikudo_t *ri,
                             grid_t   *grid)
{
    int8_t   x = 0;
    int8_t   y = 0;

    for (y = 0; y < ri->h; ++y) {
        for (x = 0; x < ri->w; ++x) {
            if (SGET(grid, x, y, ri->w) != X) {
                rikudo_case_dump(ri, grid, x, y, ri->w);
            }
        }
    }

    rikudo_trans_dump(grid, ri->src_t, ri->dst_t, ri->w, ri->nr_t);
}

static inline void rikudo_array_dump(int8_t *a,
                                     int8_t  w,
                                     int8_t  h)
{
    int8_t i = 0;
    int8_t j = 0;

    ++__Y;
    for (i = 0; i < h; i++) {
        mvprintw(__Y, 4 + X_DBG + i * 3, "%2d ", i);
        mvprintw(__Y + 1, 4 + X_DBG + i * 3, "--");
    }
    __Y += 2;

    for (i = 0; i < h; i++) {
        mvprintw(__Y, X_DBG, "%2d |", i);
        for (j = 0; j < w; ++j) {
            mvprintw(__Y, X_DBG + 4 + j * 3, "%2d", a[i * w + j]);;
        }
        ++__Y;
    }

}

void rikudo_dump(rikudo_t   *ri,
                 grid_t     *grid)
{
    uint8_t i = 0;

    __Y = 0;

    rikudo_x_main_grid_dump(ri, grid);
    rikudo_array_dump(grid->g, ri->w, ri->h);
    rikudo_array_dump(grid->s, ri->w, ri->h);

    ++__Y;
    mvprintw(__Y, X_DBG, "%2d [[", ri->nr_const);
    for (i = 0; i < ri->nr_const; ++i) {
        mvprintw(__Y, 5 + X_DBG + i * 3, "%2d", ri->lconst[i].val);
    }
    mvprintw(__Y++, 5 + X_DBG + i * 3, "]]");
    mvprintw(__Y++, X_DBG, "tested grid: %20lu", ri->nr_grid);

    refresh();
    /* getchar(); */
}

void rikudo_wait(uint32_t n)
{
    uint32_t i = 0;

    for (; i < n; ++i) {

        mvprintw(30, 0, "Root pos waiting %u/%u...", i + 1, n);
        refresh();
        sleep(1);
    }
}

#else

void rikudo_x_init(void) {}
void rikudo_x_clean(void) {}
void rikudo_dump(rikudo_t *ri, grid_t *grid) { (void)ri; (void)grid; }

void rikudo_wait(uint32_t n)
{
    uint32_t i = 0;

    for (; i < n; ++i) {
        printf("Root pos waiting %u/%u...\n", i + 1, n);
        sleep(1);
    }
}

#endif
