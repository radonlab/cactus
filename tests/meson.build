test_srcs = files(
  'buf_stream_test.c',
  'file_stream_test.c',
  'syntax/statement.c',
)

tests = executable('tests',
  test_srcs,
  files('clar.c', 'tests.c'),
  dependencies: [lib_cactus_dep, cwalk_dep]
)

test('all', tests)
