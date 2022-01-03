
tests = [
  'beginner',
  'easy',
  'medium',
]

foreach t : tests
  warning(t)

  src_test = 'test_' + t + '.c'
  warning(src_test)

  test_exec = executable(
    t,
    'test.c',
    src_test,
    src,
    include_directories: [
      inc,
      test_inc,
    ],
    c_args: flags + ['-DUNIT_TEST_TARGET'],
    dependencies: [ curses ],
  )

  test(t, test_exec)
endforeach
