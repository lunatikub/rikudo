/**
 * Do not add guards.
 * This file should be included multiple times.
 */

OPT_BOOL(pretty_print)

/**
 * The following code is used to ensure that each file which
 * includes `opt_def.h` defined all required macro.
 * It also cleans (#undef) these macros.
 */

#if !defined OPT_BOOL
  #error "Macro OPT_BOOL must be defined !"
#else
  #undef OPT_BOOL
#endif
