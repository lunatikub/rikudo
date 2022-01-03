#include <stdlib.h>

#include <rikudo.h>
#include <solve.h>

#include "test.h"
#include "test_common.h"

TEST_F(easy, 1)
{
  static const uint8_t grid[] = {
    0, 16, 54, 0, 0, 0, 1, 0, 0,  0, 13, 0, 0, 60, 0, 36, 0,  0, 0,  0,
    0, 0,  0,  0, 0, 0, 0, 0, 45, 0, 0,  0, 0, 0,  0, 21, 0,  0, 26, 0,
    0, 0,  6,  0, 0, 0, 0, 0, 49, 0, 0,  0, 0, 0,  0, 39, 32, 0, 0,  0};
  static const uint8_t expected[] = {
    18, 16, 54, 56, 57, 19, 1,  2,  17, 15, 13, 53, 55, 60, 58,
    36, 35, 20, 22, 23, 24, 3,  7,  8,  14, 12, 52, 48, 45, 44,
    59, 37, 38, 33, 34, 21, 28, 27, 26, 25, 4,  5,  6,  9,  10,
    11, 51, 50, 49, 47, 46, 43, 42, 41, 40, 39, 32, 31, 30, 29};
  static const uint8_t nr_link = 8;
  static const struct link links[] = {
    {43, 23}, {11, 26}, {22, 23}, {41, 40},
    {4, 14},  {20, 19}, {50, 49}, {16, 34},
  };

  TEST_RIKUDO(grid, EASY, expected, links, nr_link);
  return true;
}

TEST_F(easy, 2)
{
  static const uint8_t grid[] = {
    12, 0,  4, 0,  0, 10, 0,  0,  0, 16, 0, 0, 33, 0,  0, 42, 0, 0, 0,  0,
    0,  60, 0, 1,  0, 0,  25, 0,  0, 0,  0, 0, 0,  47, 0, 0,  0, 0, 57, 0,
    0,  0,  0, 20, 0, 0,  0,  27, 0, 0,  0, 0, 37, 0,  0, 0,  0, 0, 50, 0};
  static const uint8_t expected[] = {
    12, 15, 4,  5,  7,  10, 11, 13, 14, 16, 3,  24, 33, 34, 6,
    42, 8,  9,  54, 55, 56, 60, 17, 1,  2,  23, 25, 32, 31, 35,
    38, 41, 43, 47, 48, 49, 52, 53, 57, 58, 59, 18, 19, 20, 21,
    22, 26, 27, 28, 29, 30, 36, 37, 39, 40, 44, 45, 46, 50, 51};
  static const uint8_t nr_link = 6;
  static const struct link links[] = {
    {51, 29}, {37, 36}, {14, 3}, {54, 53}, {28, 27}, {42, 41},
  };

  TEST_RIKUDO(grid, EASY, expected, links, nr_link);
  return true;
}

TEST_F(easy, 3)
{
  static const uint8_t grid[] = {
    0, 0, 0,  39, 0, 0, 0, 45, 0,  34, 21, 0,  0,  0, 0, 0,  3, 1,  0, 0,
    0, 0, 0,  32, 0, 0, 0, 0,  0,  0,  0,  12, 8,  0, 0, 51, 0, 55, 0, 0,
    0, 0, 60, 0,  0, 0, 0, 0,  26, 0,  0,  0,  15, 0, 0, 0,  0, 0,  0, 0};
  static const uint8_t expected[] = {
    44, 37, 38, 39, 42, 43, 49, 45, 36, 34, 21, 20, 19, 40, 41,
    4,  3,  1,  50, 48, 47, 46, 35, 32, 33, 22, 23, 24, 18, 14,
    13, 12, 8,  5,  2,  51, 54, 55, 56, 57, 58, 59, 60, 31, 30,
    29, 28, 27, 26, 25, 17, 16, 15, 11, 10, 9,  7,  6,  52, 53};
  static const uint8_t nr_link = 6;
  static const struct link links[] = {
    {15, 33}, {28, 12}, {14, 4}, {8, 1}, {19, 6}, {22, 8},
  };

  TEST_RIKUDO(grid, EASY, expected, links, nr_link);
  return true;
}

const static struct test easy_tests[] = {
  TEST(easy, 1),
  TEST(easy, 2),
  TEST(easy, 3),
};

TEST_SUITE(easy);
