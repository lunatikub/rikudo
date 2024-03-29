#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <assert.h>

#include "pretty_print.h"
#include "opts.h"

enum cell_style {
  NORMAL = 1,
  FILLED,
  CENTER,
  START,
  LINK,
};

struct pretty_print_ctx {
  int row;
  int col;
};

/**
 * Global variable to keep informations for the
 * pretty print of a rikudo grid.
 */
static struct pretty_print_ctx ctx;

void pretty_print_init(void)
{
  if (opt_get_pretty_print() == false) {
    return;
  }
  initscr();
  getmaxyx(stdscr, ctx.row, ctx.col);
  curs_set(0);
  start_color();
  init_pair(NORMAL, COLOR_WHITE, COLOR_BLACK);
  init_pair(FILLED, COLOR_YELLOW, COLOR_BLACK);
  init_pair(CENTER, COLOR_BLUE, COLOR_BLACK);
  init_pair(START, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(LINK, COLOR_RED, COLOR_BLACK);
}

void pretty_print_exit(void)
{
  if (opt_get_pretty_print() == false) {
    return;
  }
  endwin();
}

struct coord {
  int x;
  int y;
};

static const struct coord coords[] = {
  /* circle 1 */
  /*  0 -  2 */ { 1, -1 }, { 2, 0 }, { 1, 1 },
  /*  3 -  5 */ { -1, 1 }, { -2, 0 }, { -1, -1 },
  /* circle 2 */
  /*  6 -  8 */ { 0, -2 }, { 2, -2 }, { 3, -1 },
  /*  9 - 11 */ { 4, 0 }, { 3, 1 }, { 2, 2 },
  /* 12 - 14 */ { 0, 2 }, { -2, 2 }, { -3, 1 },
  /* 15 - 17 */ { -4, 0 }, { -3, -1 }, { -2, -2 },
  /* circle 3 */
  /* 18 - 20 */ { -1, -3 }, { 1, -3 }, { 3, -3 },
  /* 21 - 23 */ { 4, -2 }, { 5, -1 }, { 6, 0 },
  /* 24 - 26 */ { 5, 1 }, { 4, 2 }, { 3, 3 },
  /* 27 - 29 */{ 1, 3 }, { -1, 3 }, { -3, 3 },
  /* 30 - 32 */ { -4, 2 }, { -5, 1 }, { -6, 0 },
  /* 33 - 35 */ { -5, -1 }, { -4, -2 }, { -3, -3 },
  /* circle 4 */
  /* 36 - 38 */ { -2, -4 }, { 0, -4 }, { 2, -4 },
  /* 39 - 41 */ { 4, -4 }, { 5, -3 }, { 6, -2 },
  /* 42 - 44 */ { 7, -1 }, { 8, 0 }, { 7, 1 },
  /* 45 - 47 */ { 6, 2 }, { 5, 3 }, { 4, 4 },
  /* 48 - 50 */ { 2, 4 }, { 0, 4 }, { -2, 4 },
  /* 51 - 53 */ { -4, 4 }, { -5, 3 }, { -6, 2 },
  /* 54 - 56 */ { -7, 1 }, { -8, 0 }, { -7, -1 },
  /* 57 - 59 */ { -6, -2 }, { -5, -3 }, { -4, -4 },
};

static inline int get_pp_x(int col, int x)
{
  return col / 2 + x * 4 - 6;
}

static inline int get_pp_y(int row, int y)
{
  return row / 2 + y * 3 - 3;
}

static inline enum cell_style get_style(const struct solver *handle, unsigned i)
{
  struct rikudo *rikudo = handle->rikudo;

  if (rikudo->grid[i] == 1 || rikudo->grid[i] == rikudo->nr) {
    return START;
  }
  if (handle->constant[rikudo->grid[i]] == true) {
    return FILLED;
  }
  return NORMAL;
}

static inline void pretty_print_cell(int x, int y, const char *str,
                                     enum cell_style style)
{
  x = get_pp_x(ctx.col, x);
  y = get_pp_y(ctx.row, y);

  attron(COLOR_PAIR(style));
  mvprintw(y - 1, x, " /   \\ ");
  mvprintw(y, x, "| %3s |", str);
  mvprintw(y + 1, x, " \\   / ");
  attroff(COLOR_PAIR(style));
}

static inline void prettry_print_cells(const struct solver *handle, const uint8_t *grid)
{
  pretty_print_cell(0, 0, "X", CENTER);
  for (unsigned i = 0; i < handle->rikudo->nr; ++i) {
    char str[3] = { };
    if (grid[i] != 0) {
      int n = sprintf(str, "%u", grid[i]);
      assert(n > 0 && n < 3);
    }
    pretty_print_cell(coords[i].x, coords[i].y, str, get_style(handle, i));
  }

}

static inline void prettry_print_link(const struct coord *c1,
                                      const struct coord *c2,
                                      unsigned x1, unsigned y1,
                                      unsigned x2, unsigned y2)
{
  attron(COLOR_PAIR(LINK));
  if (c1->x > c2->x) {
    if (c1->y > c2->y) {
      mvprintw(y1 - 1, x1 + 1, "/");
      mvprintw(y2 + 1, x2 + 5, "/");
    } else if (c1->y < c2->y) {
      mvprintw(y1 + 1, x1 + 1, "\\");
      mvprintw(y2 - 1, x2 + 5, "\\");
    } else {
      mvprintw(y1, x1, "|");
      mvprintw(y2, x2 + 6, "|");
    }
  } else {
    if (c1->y > c2->y) {
      mvprintw(y1 - 1, x1 + 5, "\\");
      mvprintw(y2 + 1, x2 + 1, "\\");
    } else if (c1->y < c2->y) {
      mvprintw(y1 + 1, x1 + 5, "/");
      mvprintw(y2 - 1, x2 + 1, "/");
    } else {
      mvprintw(y1, x2, "|");
      mvprintw(y2, x1 + 6, "|");
    }
  }
  attroff(COLOR_PAIR(LINK));
}

static inline void prettry_print_links(const struct rikudo *rikudo)
{
  for (unsigned i = 0; i < rikudo->nr_link; ++i) {
    const struct link *link = &rikudo->links[i];
    const struct coord *c1 = &coords[link->idx_1];
    const struct coord *c2 = &coords[link->idx_2];
    int x1, y1, x2, y2;
    x1 = get_pp_x(ctx.col, c1->x);
    y1 = get_pp_y(ctx.row, c1->y);
    x2 = get_pp_x(ctx.col, c2->x);
    y2 = get_pp_y(ctx.row, c2->y);
    prettry_print_link(c1, c2, x1, y1, x2, y2);
  }
}

static inline void prettry_print_meta(const struct solver *handle, uint8_t val)
{
  struct rikudo *rikudo = handle->rikudo;

  mvprintw(1, 1, "%-20s %12u", "start index", handle->start);
  mvprintw(2, 1, "%-20s %12u", "end index", handle->end);
  mvprintw(3, 1, "%-20s %12u", "number of cells", rikudo->nr);
  mvprintw(4, 1, "%-20s %12u", "number of links", rikudo->nr_link);
  mvprintw(6, 1, "%-20s %12u", "value", val);
  mvprintw(7, 1, "%-20s %12u", "failed", handle->failed);
}

static inline void pretty_print_wait(void)
{
  int step = opt_get_step_by_step();

  if (step == -1) {
    getch();
  } else if (step > 0) {
    usleep(step);
  }
}

void pretty_print_step(const struct solver *handle, uint8_t idx, uint8_t val)
{
  if (opt_get_pretty_print() == false || opt_get_step_by_step() == 0) {
    return;
  }
  prettry_print_meta(handle, val);
  prettry_print_cells(handle, handle->rikudo->grid);
  prettry_print_links(handle->rikudo);
  mvprintw(8, 1, "%-20s %12u", "current index", idx);
  refresh();
  pretty_print_wait();
}

void pretty_print_solution(const struct solver *handle)
{
  if (opt_get_pretty_print() == false) {
    return;
  }
  prettry_print_meta(handle, handle->rikudo->nr);
  prettry_print_cells(handle, handle->solution);
  prettry_print_links(handle->rikudo);
  refresh();
  getch();
}
