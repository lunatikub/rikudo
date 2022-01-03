#include <stdlib.h>

#include <rikudo.h>
#include <solve.h>

#include "test.h"
#include "test_common.h"

TEST_F(medium, 1)
{
  static const uint8_t grid[] = {
    0, 0, 32, 0, 0,  0, 12, 0,  0,  0, 0, 0, 0, 0, 0,  0, 0, 0, 14, 0,
    0, 0, 42, 0, 39, 0, 0,  36, 60, 3, 1, 0, 0, 0, 0,  0, 0, 0, 46, 0,
    0, 0, 0,  0, 0,  0, 0,  0,  0,  0, 0, 0, 0, 0, 20, 0, 0, 0, 0,  0};
  static const uint8_t expected[] = {
    30, 31, 32, 33, 9,  11, 12, 29, 43, 41, 40, 35, 34, 2,  8,
    18, 10, 13, 14, 28, 45, 44, 42, 52, 39, 38, 37, 36, 60, 3,
    1,  7,  19, 17, 16, 15, 26, 27, 46, 47, 48, 49, 50, 51, 53,
    54, 55, 56, 57, 58, 59, 4,  5,  6,  20, 21, 22, 23, 24, 25};
  static const uint8_t nr_link = 5;
  static const struct link links[] = {
    {19, 7}, {5, 16}, {23, 44}, {46, 45}, {1, 0},
  };

  TEST_RIKUDO(grid, MEDIUM, expected, links, nr_link);
  return true;
}

TEST_F(medium, 2)
{
  static const uint8_t grid[] = {
    0,  0, 25, 39, 0, 0, 0, 0, 22, 0,  0, 0, 0, 37, 0, 0, 0, 0,  58, 0,
    18, 0, 0,  0,  0, 0, 1, 0, 0,  33, 0, 0, 0, 44, 0, 0, 0, 60, 0,  0,
    0,  0, 0,  0,  0, 7, 0, 0, 0,  0,  0, 0, 0, 0,  0, 0, 0, 0,  0,  53};
  static const uint8_t expected[] = {
    23, 24, 25, 39, 40, 56, 57, 21, 22, 12, 26, 27, 29, 37, 38,
    41, 42, 55, 58, 20, 18, 14, 13, 11, 6,  5,  1,  28, 30, 33,
    36, 46, 45, 44, 43, 54, 59, 60, 19, 17, 16, 15, 10, 9,  8,
    7,  4,  3,  2,  31, 32, 34, 35, 47, 48, 49, 50, 51, 52, 53};
  static const uint8_t nr_link = 8;
  static const struct link links[] = {
    {12, 28}, {21, 22}, {6, 5}, {49, 28}, {22, 9}, {43, 42}, {44, 43}, {46, 47},
  };

  TEST_RIKUDO(grid, MEDIUM, expected, links, nr_link);
  return true;
}

TEST_F(medium, 3)
{
  static const uint8_t grid[] = {
    0, 0,  0,  0,  45, 0,  0, 0,  0, 0, 0,  0, 0,  0, 0, 0, 0, 0, 0, 0,
    0, 0,  0,  0,  0,  0,  0, 0,  0, 0, 34, 0, 51, 0, 0, 1, 6, 9, 0, 0,
    0, 13, 23, 24, 0,  28, 0, 60, 0, 0, 0,  0, 0,  0, 0, 0, 0, 0, 0, 0};
  static const uint8_t expected[] = {
    19, 40, 41, 42, 45, 18, 17, 16, 20, 39, 38, 37, 36, 35, 43,
    44, 46, 2,  7,  8,  15, 14, 21, 22, 26, 27, 30, 31, 32, 33,
    34, 53, 51, 47, 3,  1,  6,  9,  10, 11, 12, 13, 23, 24, 25,
    28, 29, 60, 59, 58, 57, 56, 55, 54, 52, 50, 49, 48, 4,  5};
  static const uint8_t nr_link = 7;
  static const struct link links[] = {
    {55, 56}, {31, 53}, {16, 33}, {11, 12}, {58, 34}, {23, 22}, {51, 50},
  };

  TEST_RIKUDO(grid, MEDIUM, expected, links, nr_link);
  return true;
}

const static struct test medium_tests[] = {
  TEST(medium, 1),
  TEST(medium, 2),
  TEST(medium, 3),
};

TEST_SUITE(medium);
