#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>

#include "opts.h"

struct options {
#define OPT_BOOL(name) bool name;

#include "opts_def.h"
};

static struct option long_options[] = {
  { "pretty-print",  no_argument,       0,  'p' },
  { 0,               0,                 0,  0 },
};

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
      default:
        return false;
    }
  }

  return true;
}

#define OPT_BOOL(name) bool opt_get_ ## name(void) { return opts.name; }

#include "opts_def.h"
