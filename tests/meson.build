test_srcs = files(
  'base/buf_stream.c',
  'base/file_stream.c',
  'syntax/statement.c',
)

tests = executable('tests',
  test_srcs,
  files('clar.c', 'tests.c'),
  dependencies: [lib_cactus_dep]
)

test('all', tests)
