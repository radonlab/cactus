#include "tests.h"

#include <stdio.h>
#include <stdlib.h>

#include "cwalk.h"

static char path_str_buf[FILENAME_MAX];

char* path_of_test_data(char* rel_path) {
  char* test_data_dir = getenv("CACTUS_TEST_DATA_DIR");
  cwk_path_join(test_data_dir, rel_path, path_str_buf, sizeof(path_str_buf));
  return path_str_buf;
}

int main(int argc, char* argv[]) { return clar_test(argc, argv); }
