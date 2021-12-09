#include "base/file_stream.h"

#include <stdio.h>
#include <stdlib.h>

#include "tests.h"
#include "cwalk.h"

static void cleanup_istream(void* opaque) {
  cac_istream_t* stream = opaque;
  cac_istream_close(stream);
}

static void cleanup_ostream(void* opaque) {
  cac_ostream_t* stream = opaque;
  cac_ostream_close(stream);
}

void test_base__file_stream__read() {
  static cac_file_istream_t file_stream;
  char namebuf[FILENAME_MAX];
  char* test_data_dir = getenv("TEST_DATA_DIR");
  char buf[5];
  size_t n;
  cwk_path_join(test_data_dir, "plain-text.txt", namebuf, sizeof(namebuf));
  FILE* file = fopen(namebuf, "r");
  cac_istream_t* stream = cac_file_istream_init(&file_stream, file);
  cl_set_cleanup(&cleanup_istream, stream);
  n = cac_istream_read(stream, (uint8_t*)buf, sizeof(buf));
  cl_assert_equal_i(n, 5);
  cl_assert_equal_strn(buf, "Lorem", n);
}

void test_base__file_stream__write() {
  static cac_file_ostream_t file_stream;
  char namebuf[FILENAME_MAX];
  char* test_data_dir = getenv("TEST_DATA_DIR");
  char* str = "Lorem ipsum dolor sit amet\n";
  size_t n;
  cwk_path_join(test_data_dir, "output-text.txt", namebuf, sizeof(namebuf));
  FILE* file = fopen(namebuf, "w");
  cac_ostream_t* stream = cac_file_ostream_init(&file_stream, file);
  cl_set_cleanup(&cleanup_ostream, stream);
  n = cac_ostream_write(stream, (uint8_t*)str, strlen(str));
  cl_assert_equal_i(n, strlen(str));
}
