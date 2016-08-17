#include <X11/extensions/XTest.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "rikudo_play.h"
#include "rikudo_macro.h"
#include "rikudo_x.h"

#define MOUSE_PAUSE (1000000)

void rikudo_play_init(rikudo_t *ri)
{
    ri->dpy = XOpenDisplay (NULL);
}

void rikudo_play_clean(rikudo_t *ri)
{
    XCloseDisplay(ri->dpy);
}

static inline void rikudo_play_root_pos_get(rikudo_t *ri)
{
    XEvent event;

    XQueryPointer(ri->dpy, RootWindow(ri->dpy, 0), &event.xbutton.root,
                  &event.xbutton.window, &event.xbutton.x_root,
                  &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y,
                  &event.xbutton.state);


    ri->mx_root = event.xbutton.x;
    ri->my_root = event.xbutton.y;
}

#define TX     (43)
#define TY     (43)
#define ROOT_X (3)
#define ROOT_Y (3)

static inline void rikudo_play_x_pos_get(rikudo_t *ri,
                                         int8_t    x,
                                         int8_t    y,
                                         uint32_t *mx,
                                         uint32_t *my)
{
    int8_t tx = x - ROOT_X;
    int8_t ty = y - ROOT_Y;

    *my = ri->my_root + (ty * TY);
    *mx = ri->mx_root + (tx * TX);

    if (ty % 2) {
        *mx -= (TX / 2);
    }
}

static inline void rikudo_play_mouse_move(rikudo_t *ri,
                                          uint32_t  mx,
                                          uint32_t  my)
{
    XTestFakeMotionEvent(ri->dpy, 0, mx, my, CurrentTime);
    XSync(ri->dpy, 0);

    XTestFakeButtonEvent(ri->dpy, 1, True,  CurrentTime);
    XTestFakeButtonEvent(ri->dpy, 1, False, CurrentTime);
}

static inline void rikudo_play_do(rikudo_t *ri,
                                  grid_t   *grid,
                                  int8_t    val,
                                  int8_t    x,
                                  int8_t    y)
{
    uint32_t mx = 0;
    uint32_t my = 0;
    pos_t dst_pos;

    if ((L_GGET(grid, x, y, dst_pos.x, dst_pos.y, ri->h, ri->w)  == val + 1) ||
        (UL_GGET(grid, x, y, dst_pos.x, dst_pos.y, ri->h, ri->w) == val + 1) ||
        (UR_GGET(grid, x, y, dst_pos.x, dst_pos.y, ri->h, ri->w) == val + 1) ||
        (R_GGET(grid, x, y, dst_pos.x, dst_pos.y, ri->h, ri->w)  == val + 1) ||
        (DL_GGET(grid, x, y, dst_pos.x, dst_pos.y, ri->h, ri->w) == val + 1) ||
        (DR_GGET(grid, x, y, dst_pos.x, dst_pos.y, ri->h, ri->w) == val + 1)) {

        rikudo_play_x_pos_get(ri, dst_pos.x, dst_pos.y, &mx, &my);
        rikudo_play_mouse_move(ri, mx, my);

        usleep(MOUSE_PAUSE);

        if (val + 1 == ri->end) {
            return;
        }

        rikudo_play_do(ri, grid, val + 1, dst_pos.x, dst_pos.y);
    }
}

#define WAIT (3)

void rikudo_play(rikudo_t *ri,
                 grid_t   *grid)
{
    rikudo_wait(WAIT);
    rikudo_play_root_pos_get(ri);
    printf("%u %u\n", ri->mx_root, ri->my_root);

    /* ri->mx_root = 2872; */
    /* ri->my_root = 376; */

    rikudo_play_do(ri, grid, 1, ri->start_pos.x, ri->start_pos.y);
}
