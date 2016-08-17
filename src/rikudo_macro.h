#ifndef RIKUDO_MACRO_H_
# define RIKUDO_MACRO_H_

/**
 *   UL   UR
 * L    X    R
 *   DL   DR
 */

#define L_SGET(_g,_sx,_sy,_dx,_dy,_h,_w)        \
    ({                                          \
        int8_t v = -3;                          \
        _dx = _sx - 1;                          \
        _dy = _sy;                              \
        if (_sx > 0)                            \
            v = (_g)->s[_dy * _w + _dx];        \
        v;                                      \
    })                                          \

#define R_SGET(_g,_sx,_sy,_dx,_dy,_h,_w)        \
    ({                                          \
        int8_t v = -3;                          \
        _dx = _sx + 1;                          \
        _dy = _sy;                              \
        if (_sx < _w - 1)                       \
            v = (_g)->s[_dy * _w + _dx];        \
        v;                                      \
    })                                          \

#define DR_SGET(_g,_sx,_sy,_dx,_dy,_h,_w)       \
    ({                                          \
        int8_t v = -3;                          \
        if (_sy % 2 == 0) {                     \
            _dx = _sx;                          \
            _dy = _sy + 1;                      \
            if (_sy < _h - 1)                   \
                v = (_g)->s[_dy * _w + _dx];    \
        } else {                                \
            _dx = _sx + 1;                      \
            _dy = _sy + 1;                      \
            if (_sy < _h - 1 && _sx < _w - 1)   \
                v = (_g)->s[_dy * _w + _dx];    \
        }                                       \
        v;                                      \
    })                                          \

#define DL_SGET(_g,_sx,_sy,_dx,_dy,_h,_w)       \
    ({                                          \
        int8_t v = -3;                          \
        if (_sy % 2 == 0) {                     \
            _dx = _sx - 1;                      \
            _dy = _sy + 1;                      \
            if (_sx > 0 && _sy < _h - 1)        \
                v = (_g)->s[_dy * _w + _dx];    \
        } else {                                \
            _dx = _sx;                          \
            _dy = _sy + 1;                      \
            if (_sy < _h - 1)                   \
                v = (_g)->s[_dy * _w + _dx];    \
        }                                       \
        v;                                      \
    })                                          \

#define UR_SGET(_g,_sx,_sy,_dx,_dy,_h,_w)       \
    ({                                          \
        int8_t v = -3;                          \
        if (_sy % 2 == 0) {                     \
            _dx = _sx;                          \
            _dy = _sy - 1;                      \
            if (_sy > 0)                        \
                v = (_g)->s[_dy * _w + _dx];    \
        } else {                                \
            _dx = _sx + 1;                      \
            _dy = _sy - 1;                      \
            if (_sy > 0 && _sx < _w - 1)        \
                v = (_g)->s[_dy * _w + _dx];    \
        }                                       \
        v;                                      \
    })                                          \

#define UL_SGET(_g,_sx,_sy,_dx,_dy,_h,_w)       \
    ({                                          \
        int8_t v = -3;                          \
        if (_sy % 2 == 0) {                     \
            _dx = _sx - 1;                      \
            _dy = _sy - 1;                      \
            if (_sx > 0 && _sy > 0)             \
                v = (_g)->s[_dy * _w + _dx];    \
        } else {                                \
            _dx = _sx;                          \
            _dy = _sy - 1;                      \
            if (_sy > 0)                        \
                v = (_g)->s[_dy * _w + _dx];    \
        }                                       \
        v;                                      \
    })                                          \

#define L_GGET(_g,_sx,_sy,_dx,_dy,_h,_w)        \
    ({                                          \
        int8_t v = -3;                          \
        _dx = _sx - 1;                          \
        _dy = _sy;                              \
        if (_sx > 0)                            \
            v = (_g)->g[_dy * _w + _dx];        \
        v;                                      \
    })                                          \

#define R_GGET(_g,_sx,_sy,_dx,_dy,_h,_w)        \
    ({                                          \
        int8_t v = -3;                          \
        _dx = _sx + 1;                          \
        _dy = _sy;                              \
        if (_sx < _w - 1)                       \
            v = (_g)->g[_dy * _w + _dx];        \
        v;                                      \
    })                                          \

#define DR_GGET(_g,_sx,_sy,_dx,_dy,_h,_w)       \
    ({                                          \
        int8_t v = -3;                          \
        if (_sy % 2 == 0) {                     \
            _dx = _sx;                          \
            _dy = _sy + 1;                      \
            if (_sy < _h - 1)                   \
                v = (_g)->g[_dy * _w + _dx];    \
        } else {                                \
            _dx = _sx + 1;                      \
            _dy = _sy + 1;                      \
            if (_sy < _h - 1 && _sx < _w - 1)   \
                v = (_g)->g[_dy * _w + _dx];    \
        }                                       \
        v;                                      \
    })                                          \

#define DL_GGET(_g,_sx,_sy,_dx,_dy,_h,_w)       \
    ({                                          \
        int8_t v = -3;                          \
        if (_sy % 2 == 0) {                     \
            _dx = _sx - 1;                      \
            _dy = _sy + 1;                      \
            if (_sx > 0 && _sy < _h - 1)        \
                v = (_g)->g[_dy * _w + _dx];    \
        } else {                                \
            _dx = _sx;                          \
            _dy = _sy + 1;                      \
            if (_sy < _h - 1)                   \
                v = (_g)->g[_dy * _w + _dx];    \
        }                                       \
        v;                                      \
    })                                          \

#define UR_GGET(_g,_sx,_sy,_dx,_dy,_h,_w)       \
    ({                                          \
        int8_t v = -3;                          \
        if (_sy % 2 == 0) {                     \
            _dx = _sx;                          \
            _dy = _sy - 1;                      \
            if (_sy > 0)                        \
                v = (_g)->g[_dy * _w + _dx];    \
        } else {                                \
            _dx = _sx + 1;                      \
            _dy = _sy - 1;                      \
            if (_sy > 0 && _sx < _w - 1)        \
                v = (_g)->g[_dy * _w + _dx];    \
        }                                       \
        v;                                      \
    })                                          \

#define UL_GGET(_g,_sx,_sy,_dx,_dy,_h,_w)       \
    ({                                          \
        int8_t v = -3;                          \
        if (_sy % 2 == 0) {                     \
            _dx = _sx - 1;                      \
            _dy = _sy - 1;                      \
            if (_sx > 0 && _sy > 0)             \
                v = (_g)->g[_dy * _w + _dx];    \
        } else {                                \
            _dx = _sx;                          \
            _dy = _sy - 1;                      \
            if (_sy > 0)                        \
                v = (_g)->g[_dy * _w + _dx];    \
        }                                       \
        v;                                      \
    })                                          \

#define GGET(_g,_x,_y,_w)    ((_g)->g[(_x) + (_y) * (_w)])
#define GSET(_g,_x,_y,_w,_v) ((_g)->g[(_x) + (_y) * (_w)] = (_v))
#define SGET(_g,_x,_y,_w)    ((_g)->s[(_x) + (_y) * (_w)])
#define SSET(_g,_x,_y,_w,_v) ((_g)->s[(_x) + (_y) * (_w)] = (_v))

#endif /* !RIKUDO_MACRO_H_ */
