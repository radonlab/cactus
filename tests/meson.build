test_srcs = files(
  'base/buf_stream.c',
  'base/file_stream.c',
  'syntax/statement.c',
)

test_srcs += files('clar.c', 'tests.c')

tests = executable('tests',
  test_srcs,
)

test('all', tests)
