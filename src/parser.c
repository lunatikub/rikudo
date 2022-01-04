#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "rikudo.h"
#include "parser.h"

#define COMMA ','

#define IS_DIGIT(x) (x >= '0' && x <= '9')

enum token {
  TOKEN_COMMA,
  TOKEN_VALUE,
  TOKEN_END,
};

struct lexer {
  const char *str;
  uint32_t len;
  enum token token;
  uint32_t offset_start;
  uint32_t offset_end;
};

static inline int lexer_comma(struct lexer *lexer)
{
  lexer->token = TOKEN_COMMA;
  ++lexer->offset_end;
  return true;
}

static inline int lexer_value(struct lexer *lexer)
{
  while (IS_DIGIT(lexer->str[lexer->offset_end]) &&
         lexer->offset_end < lexer->len) {
    ++lexer->offset_end;
  }
  lexer->token = TOKEN_VALUE;
  return true;
}

static inline void lexer_skip(struct lexer *lexer)
{
  while (lexer->offset_start < lexer->len &&
         lexer->str[lexer->offset_start] == ' ') {
    ++lexer->offset_start;
  }
  lexer->offset_end = lexer->offset_start;
}

static inline bool lexer_token_fill(struct lexer *lexer)
{
  lexer_skip(lexer);

  if (lexer->offset_end == lexer->len) {
    lexer->token = TOKEN_END;
    return true;
  }

  char c = lexer->str[lexer->offset_start];

  if (c == COMMA) {
    return lexer_comma(lexer);
  }
  if (IS_DIGIT(c)) {
    return lexer_value(lexer);
  }

  return false;
}

static inline void lexer_token_eat(struct lexer *lexer)
{
  lexer->offset_start = lexer->offset_end;
}

static inline bool strtoint(const char *start, const char *end, int *v)
{
  char *endptr = NULL;
  long val;

  val = strtol(start, &endptr, 10);
  if (endptr != end) {
    return false;
  }
  *v = val;

  return true;
}

static inline bool add_cell(struct lexer *lexer, uint8_t *grid, uint8_t *n)
{
  int val;
  const char *start = &lexer->str[lexer->offset_start];
  const char *end = &lexer->str[lexer->offset_end];
  if (strtoint(start, end, &val) == false) {
    return false;
  }
  grid[*n] = val;
  ++(*n);
  return true;
}

bool grid_parse(const char *str, uint8_t *grid, uint8_t nr)
{
  struct lexer lexer = {
    .str = str,
    .len = strlen(str),
    .offset_start = 0,
    .offset_end = 0,
  };

  uint8_t n = 0;

  while (true) {
    /* value */
    if (lexer_token_fill(&lexer) == false) {
      return false;
    }
    if (lexer.token != TOKEN_VALUE) {
      return false;
    }
    if (add_cell(&lexer, grid, &n) == false) {
      return false;
    }
    lexer_token_eat(&lexer);
    /* command or end */
    if (lexer_token_fill(&lexer) == false) {
      return false;
    }
    if (lexer.token == TOKEN_END) {
      break;
    }
    if (lexer.token != TOKEN_COMMA) {
      return false;
    }
    lexer_token_eat(&lexer);
  }

  return n == nr;
}

static const uint8_t nr_from_level[] = {
  [BEGINNER] = 36,
  [EASY] = 60,
  [MEDIUM] = 60,
  [HARD] = 90,
  [EVIL] = 90,
  [XL] = 126,
};

bool level_parse(enum level level, uint8_t *nr)
{
  if (level >= BEGINNER && level <= XL) {
    *nr = nr_from_level[level];
    return true;
  }
  return false;
}

static inline int get_index(const char *start, unsigned off, unsigned len)

{
  char tmp[128];

  strncpy(tmp, start + off, len);
  tmp[len] = 0;
  return atoi(tmp) - 1;
}

static inline bool add_link(struct lexer *lexer, struct link *links, uint8_t *n)
{
  const char *start = &lexer->str[lexer->offset_start];
  const char *end = &lexer->str[lexer->offset_end];

  static int len_1;
  static int len_2;
  static int turn = 0;
  int idx_1, idx_2;

  if (turn % 2 == 0) {
    len_1 = (int)(end - start);
  } else {
    len_2 = (int)(end - start);
    if (len_1 == 5) {
      if (len_2 == 5) {
        idx_1 = get_index(start, 0, 2);
        idx_2 = get_index(start, 3, 2);
      } else {
        idx_1 = get_index(start, 0, 1);
        idx_2 = get_index(start, 2, 2);
      }
    } else {
      if (len_2 == 5) {
        idx_1 = get_index(start, 0, 2);
        idx_2 = get_index(start, 4, 1);
      } else {
        idx_1 = get_index(start, 0, 1);
        idx_2 = get_index(start, 3, 1);
      }
    }
    links[*n].idx_1 = idx_1;
    links[*n].idx_2 = idx_2;
    ++(*n);
  }

  ++turn;
  return true;
}

bool links_parse(const char *str, struct link *links, uint8_t nr)
{
  struct lexer lexer = {
    .str = str,
    .len = strlen(str),
    .offset_start = 0,
    .offset_end = 0,
  };

  uint8_t n = 0;

  while (true) {
    /* value */
    if (lexer_token_fill(&lexer) == false) {
      return false;
    }
    if (lexer.token != TOKEN_VALUE) {
      return false;
    }
    if (add_link(&lexer, links, &n) == false) {
      return false;
    }
    lexer_token_eat(&lexer);
    /* command or end */
    if (lexer_token_fill(&lexer) == false) {
      return false;
    }
    if (lexer.token == TOKEN_END) {
      break;
    }
    if (lexer.token != TOKEN_COMMA) {
      return false;
    }
    lexer_token_eat(&lexer);
  }

  return n == nr;
}
