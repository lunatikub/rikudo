#include <stdlib.h>
#include <ncurses.h>
#include <assert.h>

#include "pretty_print.h"

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

static struct pretty_print_ctx ctx;

void pretty_print_init(void)
{
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
  endwin();
}

struct coord {
  int x;
  int y;
};

static const struct coord coords[] = {
  /* circle 1 */
  { 1, -1 }, { 2, 0 }, { 1, 1 },
  { -1, 1 }, { -2, 0 }, { -1, -1 },
  /* circle 2 */
  { 0, -2 }, { 2, -2 }, { 3, -1 },
  { 4, 0 }, { 3, 1 }, { 2, 2 },
  { 0, 2 }, { -2, 2 }, { -3, 1 },
  { -4, 0 }, { -3, -1 }, { -2, -2 },
  /* circle 3 */
  { -1, -3 }, { 1, -3 }, { 3, -3 },
  { 4, -2 }, { 5, -1 }, { 6, 0 },
  { 5, 1 }, { 4, 2 }, { 3, 3 },
  { 1, 3 }, { -1, 3 }, { -3, 3 },
  { -4, 2 }, { -5, 1 }, { -6, 0 },
  { -5, -1 }, { -4, -2 }, { -3, -3 },
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
      assert("!(prettry print link 1)");
    } else {
      mvprintw(y1, x1, "|");
      mvprintw(y2, x2 + 6, "|");
    }
  } else {
    if (c1->y > c2->y) {
      mvprintw(y1 - 1, x1 + 5, "\\");
      mvprintw(y2 + 1, x2 + 1, "\\");
    } else if (c1->y < c2->y) {
      assert("!(prettry print link 2)");
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
  mvprintw(7, 1, "%-20s %12u", "failed", handle->failed);}

void pretty_print_refresh(const struct solver *handle, uint8_t idx, uint8_t val)
{
  prettry_print_meta(handle, val);
  prettry_print_cells(handle, handle->rikudo->grid);
  prettry_print_links(handle->rikudo);
  mvprintw(8, 1, "%-20s %12u", "current index", idx);
  refresh();
  getch();
}

void pretty_print_solution(const struct solver *handle)
{
  prettry_print_meta(handle, handle->rikudo->nr);
  prettry_print_cells(handle, handle->solution);
  prettry_print_links(handle->rikudo);
  refresh();
  getch();
}
