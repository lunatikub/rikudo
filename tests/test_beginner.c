#include <stdlib.h>

#include <rikudo.h>
#include <solve.h>

#include "test.h"
#include "test_common.h"

TEST_F(beginner, 1)
{
  static const uint8_t grid[] = {0, 0, 10, 0, 0, 19, 0,  31, 33, 0, 36, 7,
                                 0, 0, 0,  0, 0, 26, 28, 0,  0,  0, 1,  3,
                                 0, 0, 0,  0, 0, 14, 0,  0,  22, 0, 0,  0};
  static const uint8_t expected[] = {
    34, 35, 10, 11, 18, 19, 27, 31, 33, 2, 36, 7,  9,  12, 17, 21, 20, 26,
    28, 29, 30, 32, 1,  3,  4,  5,  6,  8, 13, 14, 15, 16, 22, 23, 24, 25};
  static const uint8_t nr_link = 4;
  static const struct link links[] = {
    {28, 13}, {4, 14}, {13, 3}, {31, 14},
  };

  TEST_RIKUDO(grid, BEGINNER, expected, links, nr_link);
  return true;
}

TEST_F(beginner, 2)
{
  static const uint8_t grid[] = {0,  32, 0, 36, 0, 0, 0, 0,  15, 0,  0,  0,
                                 0,  4,  0, 28, 0, 0, 0, 20, 0,  0,  16, 0,
                                 12, 0,  0, 0,  7, 0, 0, 0,  1,  26, 0,  0};
  static const uint8_t expected[] = {
    31, 32, 34, 36, 29, 30, 21, 18, 15, 14, 33, 9, 35, 4, 3, 28, 27, 22,
    23, 20, 19, 17, 16, 13, 12, 11, 10, 8,  7,  6, 5,  2, 1, 26, 25, 24};
  static const uint8_t nr_link = 5;
  static const struct link links[] = {
    {26, 25}, {7, 21}, {12, 2}, {34, 35}, {18, 35},
  };

  TEST_RIKUDO(grid, BEGINNER, expected, links, nr_link);
  return true;
}

TEST_F(beginner, 3)
{
  static const uint8_t grid[] = {36, 0, 0, 0,  0, 1, 0, 25, 29, 30, 0,  6,
                                 4,  0, 0, 15, 0, 0, 0, 0,  0,  0,  0,  0,
                                 33, 0, 0, 9,  0, 0, 0, 0,  0,  18, 21, 0};
  static const uint8_t expected[] = {
    36, 35, 5,  3,  2,  1,  24, 25, 29, 30, 34, 6,  4,  11, 14, 15, 19, 20,
    23, 26, 27, 28, 31, 32, 33, 7,  8,  9,  10, 12, 13, 16, 17, 18, 21, 22};
  static const uint8_t nr_link = 4;
  static const struct link links[] = {
    {1, 10}, {26, 25}, {13, 28}, {35, 18},
  };

  TEST_RIKUDO(grid, BEGINNER, expected, links, nr_link);
  return true;
}

const static struct test beginner_tests[] = {
  TEST(beginner, 1),
  TEST(beginner, 2),
  TEST(beginner, 3),
};

TEST_SUITE(beginner);
