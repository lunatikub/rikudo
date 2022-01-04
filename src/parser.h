#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdint.h>

#include "rikudo.h"

/** All the following formats to parse are extracted from the site: rikudo.fr **/

/**
 * Parse a grid with the format "x1, x2, x3, x4 ...".
 */
bool grid_parse(const char *str, uint8_t *grid, uint8_t nr);

/**
 * Parse the level of a rikudo and set the number of cells.
 */
bool level_parse(enum level level, uint8_t *nr);

/**
 * Parse the links with the format "l1_1, l1_2, ...".
 */
bool links_parse(const char *str, struct link *links, uint8_t nr);

#endif /* !_PARSER_H__ */
