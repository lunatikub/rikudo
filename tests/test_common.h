#ifndef __TEST_COMMON_H__
#define __TEST_COMMON_H__

#define TEST_RIKUDO(GRID, LVL, EXPECTED, LINKS, NR_LINK)                \
  do {                                                                  \
    struct rikudo *rikudo = rikudo_create(GRID, LVL, LINKS, NR_LINK);   \
    uint8_t *solution = rikudo_solve(rikudo);                           \
    EXPECT_TRUE(solution != NULL);                                      \
    EXPECT_TRUE(memcmp(solution, expected,                              \
                       sizeof(expected) / sizeof(uint8_t)) == 0);       \
    free(solution);                                                     \
    rikudo_destroy(rikudo);                                             \
  } while(0)

#endif /* !__TEST_COMMON_H__ */
