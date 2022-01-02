#include <rikudo.h>

#include "test.h"

TEST_F(create, 1)
{
  static const uint8_t grid[] = {0,  0, 0, 1,  0, 0, 0, 0, 0,  17, 22, 36,
                                 0,  0, 0, 0,  3, 0, 0, 0, 12, 0,  0,  0,
                                 20, 0, 0, 34, 0, 0, 0, 0, 0,  28, 7,  0};
  static const uint8_t nr_link = 5;
  static const struct link links[] = {
    {6, 7}, {23, 24}, {16, 15}, {20, 19}, {18, 7},
  };

  struct rikudo *rikudo = rikudo_create(grid, BEGINNER, links, nr_link);

  rikudo_destroy(rikudo);
  return true;
}

TEST_F(create, 2)
{
  static const uint8_t grid[] = {0, 1, 0,  0,  0, 0,  0, 0, 15, 0,  0, 0,
                                 4, 0, 24, 29, 0, 19, 0, 0, 36, 0,  0, 12,
                                 9, 0, 0,  0,  0, 26, 0, 0, 0,  31, 0, 0};
  static const uint8_t nr_link = 3;
  static const struct link links[] = {
    {6, 5}, {1, 7}, {36, 35},
  };

  struct rikudo *rikudo = rikudo_create(grid, BEGINNER, links, nr_link);

  rikudo_destroy(rikudo);
  return true;
}

const static struct test create_tests[] = {
  TEST(create, 1),
  TEST(create, 2),
};

TEST_SUITE(create);
