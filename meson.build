project('cactus', 'c',
  version: '0.1',
  default_options: ['warning_level=3']
)

inc_dir = include_directories('include')

srcs = files('src/parser/grammar.c', 'src/main.c')

executable('cactus',
  srcs,
  include_directories: [inc_dir],
  install: true
)

if not get_option('tests').disabled()
  subdir('tests')
endif
