project('cactus', 'c',
  version: '0.1',
  default_options: ['warning_level=3']
)

inc_dir = include_directories('include')
src_dir = include_directories('src')

srcs = files(
  'src/base/buf_stream.c',
  'src/base/common.c',
  'src/base/file_stream.c',
  'src/base/stream.c',
  'src/parser/grammar.c',
  'src/main.c',
)

executable('cactus',
  srcs,
  include_directories: [inc_dir, src_dir],
  install: true
)

if not get_option('tests').disabled()
  subdir('tests')
endif
