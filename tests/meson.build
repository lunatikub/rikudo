
test_create = executable(
  'create',
  'test.c',
  'test_create.c',
  src,
  include_directories: [
    inc,
    test_inc,
  ],
  c_args: flags + ['-DUNIT_TEST_TARGET'],
  dependencies: [ curses ],
)

test('create', test_create)
