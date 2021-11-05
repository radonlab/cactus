project('cactus', 'c',
  version: '0.1',
  default_options: ['warning_level=3']
)

lib_srcs = files(
  'src/base/buf_stream.c',
  'src/base/common.c',
  'src/base/file_stream.c',
  'src/base/stream.c',
  'src/parser/grammar.c',
)

lib_cactus = shared_library('cactus',
  lib_srcs,
  include_directories: include_directories(['include', 'src']),
  install: true
)

lib_cactus_dep = declare_dependency(
  link_with: lib_cactus,
  include_directories: include_directories(['include', 'src'])
)

cwalk_proj = subproject('cwalk')
cwalk_dep = cwalk_proj.get_variable('cwalk_dep')

executable('cactus',
  files('src/main.c'),
  dependencies: [lib_cactus_dep, cwalk_dep],
  install: true
)

if not get_option('tests').disabled()
  subdir('tests')
endif
