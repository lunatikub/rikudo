#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdint.h>

/**
 * Parse a grid with the format "x1, x2, x3, x4 ...".
 */
bool parse_grid(const char *str, uint8_t *grid, uint8_t nr);

/**
 * Parse the level of a rikudo.
 */
bool parse_level(const char *str, enum level *level, uint8_t *nr);

#endif /* !_PARSER_H__ */
