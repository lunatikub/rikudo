#include <rikudo.h>

#include "test.h"

TEST_F(beginner, 1)
{
  static const uint8_t grid[] = {0,  0, 0, 1,  0, 0, 0, 0, 0,  17, 22, 36,
                                 0,  0, 0, 0,  3, 0, 0, 0, 12, 0,  0,  0,
                                 20, 0, 0, 34, 0, 0, 0, 0, 0,  28, 7,  0};

  static const uint8_t solution[] = {
    15, 16, 23, 1,  2,  4,  5,  11, 14, 17, 22, 36, 24, 25, 26, 27, 3, 6,
    9,  10, 12, 13, 18, 19, 20, 21, 35, 34, 33, 32, 31, 30, 29, 28, 7, 8};

  static const uint8_t nr_link = 5;
  static const struct link links[] = {
    {6, 7}, {23, 24}, {16, 15}, {20, 19}, {18, 7},
  };

  struct rikudo *rikudo = rikudo_create(grid, BEGINNER, links, nr_link);

  EXPECT_TRUE(rikudo->start == 3);
  EXPECT_TRUE(rikudo->end == 11);

  (void)solution;

  rikudo_destroy(rikudo);
  return true;
}

TEST_F(beginner, 2)
{
  static const uint8_t grid[] = {0, 1, 0,  0,  0, 0,  0, 0, 15, 0,  0, 0,
                                 4, 0, 24, 29, 0, 19, 0, 0, 36, 0,  0, 12,
                                 9, 0, 0,  0,  0, 26, 0, 0, 0,  31, 0, 0};

  static const uint8_t solution[] = {
    17, 1,  2,  23, 22, 21, 18, 16, 15, 11, 10, 3,  4,  25, 24, 29, 20, 19,
    34, 35, 36, 14, 13, 12, 9,  8,  7,  6,  5,  26, 27, 28, 30, 31, 32, 33};

  static const uint8_t nr_link = 3;
  static const struct link links[] = {
    {6, 5}, {1, 7}, {36, 35},
  };

  struct rikudo *rikudo = rikudo_create(grid, BEGINNER, links, nr_link);

  EXPECT_TRUE(rikudo->start == 1);
  EXPECT_TRUE(rikudo->end == 20);

  (void)solution;

  rikudo_destroy(rikudo);
  return true;
}

TEST_F(beginner, 3)
{
  static const uint8_t grid[] = {6, 29, 0,  19, 0, 0,  0, 1, 0,  31, 27, 0,
                                 0, 0,  0,  0,  0, 9,  0, 0, 0,  0,  0,  33,
                                 0, 0,  36, 0,  0, 23, 0, 0, 15, 0,  12, 0};

  static const uint8_t solution[] = {
    6,  29, 28, 19, 18, 7,  5,  1,  30, 31, 27, 26, 20, 21, 17, 14, 8,  9,
    10, 4,  3,  2,  32, 33, 34, 35, 36, 25, 24, 23, 22, 16, 15, 13, 12, 11};

  static const uint8_t nr_link = 3;
  static const struct link links[] = {
    {32, 15}, {20, 7}, {22, 21},
  };

  struct rikudo *rikudo = rikudo_create(grid, BEGINNER, links, nr_link);

  EXPECT_TRUE(rikudo->start == 7);
  EXPECT_TRUE(rikudo->end == 26);

  (void)solution;

  rikudo_destroy(rikudo);
  return true;
}

const static struct test beginner_tests[] = {
  TEST(beginner, 1),
  TEST(beginner, 2),
  TEST(beginner, 3),
};

TEST_SUITE(beginner);
