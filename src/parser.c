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

static inline bool add_value(struct lexer *lexer, uint8_t *grid, uint8_t *n)
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

bool parse_grid(const char *str, uint8_t *grid, uint8_t nr)
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
    if (add_value(&lexer, grid, &n) == false) {
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

bool parse_level(const char *str, enum level *level, uint8_t *nr)
{
  int v;
  const char *end = str + strlen(str);
  if (strtoint(str, end, &v) == false) {
    return false;
  }
  if (v >= BEGINNER && v <= XL) {
    *level = v;
    return true;
  }
  *nr = nr_from_level[level];
  return false;
}
