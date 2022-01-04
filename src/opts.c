#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>

#include "opts.h"

struct options {
#define OPT_BOOL(name) bool name;
#define OPT_INT(name) int name;
#define OPT_STR(name) char *name;
#include "opts_def.h"
};

static struct option long_options[] = {
  { "pretty-print",  no_argument,       0, 'p' },
  { "step-by-step",  required_argument, 0, 's' },
  { "grid",          required_argument, 0, 'g' },
  { "level",         required_argument, 0, 'l' },
  { "nr-link",       required_argument, 0, 'n' },
  { "links",         required_argument, 0, 'z' },
  { 0,               0,                 0,  0 },
};

/**
 * Use the getters to get all option
 * values from all sources.
 */
static struct options opts;

static inline bool check_mandatory_opts(void)
{
  if (opts.grid == NULL) {
    fprintf(stderr, "option '--grid' is mandatory...\n");
    return false;
  }
  if (opts.level == 0) {
    fprintf(stderr, "options '--level' is mandatory...\n");
    return false;
  }
  if (opts.nr_link == 0) {
    fprintf(stderr, "options '--nr-link' is mandatory...\n");
    return false;
  }
  if (opts.links == NULL) {
    fprintf(stderr, "option '--links' is mandatory...\n");
    return false;
  }
  return true;
}

void options_clean(void)
{
  free(opts.grid);
  free(opts.links);
}

bool options_parse(int argc, char **argv)
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
      case 'g':
        opts.grid = strdup(optarg);
        break;
      case 'l':
        opts.level = atoi(optarg);;
        break;
      case 'n':
        opts.nr_link = atoi(optarg);
        break;
      case 'z':
        opts.links = strdup(optarg);
        break;
      default:
        return false;
    }
  }

  return check_mandatory_opts();
}

#define OPT_BOOL(name) bool opt_get_ ## name(void) { return opts.name; }
#define OPT_INT(name) int opt_get_ ## name(void) { return opts.name; }
#define OPT_STR(name) char* opt_get_ ## name(void) { return opts.name; }

#include "opts_def.h"
