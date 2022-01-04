/**
 * Do not add guards.
 * This file should be included multiple times.
 */

OPT_BOOL(pretty_print)
OPT_INT(step_by_step)
OPT_STR(grid)

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

#if !defined OPT_INT
  #error "Macro OPT_INT must be defined !"
#else
  #undef OPT_INT
#endif

#if !defined OPT_STR
  #error "Macro OPT_STR must be defined !"
#else
  #undef OPT_STR
#endif
