#include "base/file_stream.h"

#include <stdio.h>

#include "tests.h"

static void cleanup_istream(void* opaque) {
  cac_istream_t* stream = opaque;
  cac_istream_close(stream);
}

static void cleanup_ostream(void* opaque) {
  cac_ostream_t* stream = opaque;
  cac_ostream_close(stream);
}

void test_base__file_stream__read() {
  char* filepath = path_of_test_data("plain-text.txt");
  FILE* file = fopen(filepath, "r");
  char buf[5];
  size_t n;
  static cac_file_istream_t file_stream;
  cac_istream_t* stream = cac_file_istream_init(&file_stream, file);
  cl_set_cleanup(&cleanup_istream, stream);
  n = cac_istream_read(stream, (uint8_t*)buf, sizeof(buf));
  cl_assert_equal_i(n, 5);
  cl_assert_equal_strn(buf, "Lorem", n);
}

void test_base__file_stream__write() {
  char* filepath = path_of_test_data("output-text.txt");
  FILE* file = fopen(filepath, "w");
  char* str = "Lorem ipsum dolor sit amet\n";
  size_t n;
  static cac_file_ostream_t file_stream;
  cac_ostream_t* stream = cac_file_ostream_init(&file_stream, file);
  cl_set_cleanup(&cleanup_ostream, stream);
  n = cac_ostream_write(stream, (uint8_t*)str, strlen(str));
  cl_assert_equal_i(n, strlen(str));
}
