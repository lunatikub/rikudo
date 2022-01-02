
test_beginner = executable(
  'beginner',
  'test.c',
  'test_beginner.c',
  src,
  include_directories: [
    inc,
    test_inc,
  ],
  c_args: flags + ['-DUNIT_TEST_TARGET'],
  dependencies: [ curses ],
)

test('beginner', test_beginner)

test_easy = executable(
  'easy',
  'test.c',
  'test_easy.c',
  src,
  include_directories: [
    inc,
    test_inc,
  ],
  c_args: flags + ['-DUNIT_TEST_TARGET'],
  dependencies: [ curses ],
)

test('easy', test_easy)
