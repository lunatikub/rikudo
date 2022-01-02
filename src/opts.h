#ifndef __OPTS_H__
#define __OPTS_H__

/**
 * Parse the options given in arguments.
 * All available options are defined in 'options.c'.
 */
bool parse_options(int argc, char **argv);

/**
 * Getters.
 */
#define OPT_BOOL(name) bool opt_get_ ## name(void);
#define OPT_INT(name) int opt_get_ ## name(void);

#include "opts_def.h"

#endif /* !__OPTS_H__ */
