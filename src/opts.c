#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>

#include "opts.h"

struct options {
#define OPT_BOOL(name) bool name;
#define OPT_INT(name) int name;
#include "opts_def.h"
};

static struct option long_options[] = {
  { "pretty-print",  no_argument,       0, 'p' },
  { "step-by-step",  required_argument, 0, 's' },
  { 0,               0,                 0,  0 },
};

/**
 * Use the getters to get all option
 * values from all sources.
 */
static struct options opts;

bool parse_options(int argc, char **argv)
{
  int c;

  while (true) {
    int option_index = 0;

    c = getopt_long(argc, argv, "", long_options, &option_index);
    if (c == -1) {
      break;
    }

    switch (c) {
      case 'p':
        opts.pretty_print = true;
        break;
      case 's':
        opts.step_by_step = atoi(optarg);
        break;
      default:
        return false;
    }
  }

  return true;
}

#define OPT_BOOL(name) bool opt_get_ ## name(void) { return opts.name; }
#define OPT_INT(name) int opt_get_ ## name(void) { return opts.name; }

#include "opts_def.h"
