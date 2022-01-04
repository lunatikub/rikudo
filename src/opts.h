#ifndef __OPTS_H__
#define __OPTS_H__

/**
 * Parse the options given in arguments.
 * All available options are defined in 'options.c'.
 */
bool options_parse(int argc, char **argv);

/**
 * Clean/free all options.
 */
void options_clean(void);

/**
 * Getters.
 */
#define OPT_BOOL(name) bool opt_get_ ## name(void);
#define OPT_INT(name) int opt_get_ ## name(void);
#define OPT_STR(name) char* opt_get_ ## name(void);

#include "opts_def.h"

#endif /* !__OPTS_H__ */
