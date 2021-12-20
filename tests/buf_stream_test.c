#include "base/buf_stream.h"

#include <string.h>

#include "tests.h"

static void cleanup_istream(void* opaque) {
  cac_istream_t* stream = opaque;
  cac_istream_close(stream);
}

static void cleanup_ostream(void* opaque) {
  cac_ostream_t* stream = opaque;
  cac_ostream_close(stream);
}

void test_base__buf_stream__read() {
  char* str = "foobarbaz";
  char buf[5];
  size_t n;
  static cac_buf_istream_t buf_stream;
  cac_istream_t* stream = cac_buf_istream_init(&buf_stream, (uint8_t*)str, strlen(str));
  cl_set_cleanup(&cleanup_istream, stream);
  n = cac_istream_read(stream, (uint8_t*)buf, sizeof(buf));
  cl_assert_equal_i(n, 5);
  cl_assert_equal_strn(buf, "fooba", n);
  n = cac_istream_read(stream, (uint8_t*)buf, sizeof(buf));
  cl_assert_equal_i(n, 4);
  cl_assert_equal_strn(buf, "rbaz", n);
  n = cac_istream_read(stream, (uint8_t*)buf, 1);
  cl_assert_equal_i(n, 0);
  cl_assert_equal_i(buf_stream.offset, buf_stream.size);
}

void test_base__buf_stream__write() {
  char* str1 = "foo";
  char* str2 = "bar";
  char str3[2048];
  size_t total = 0;
  size_t n;
  static cac_buf_ostream_t buf_stream;
  cac_ostream_t* stream = cac_buf_ostream_init(&buf_stream, 0);
  cl_set_cleanup(&cleanup_ostream, stream);
  n = cac_ostream_write(stream, (uint8_t*)str1, strlen(str1));
  total += n;
  cl_assert_equal_i(n, 3);
  n = cac_ostream_write(stream, (uint8_t*)str2, strlen(str2));
  total += n;
  cl_assert_equal_i(n, 3);
  cl_assert_equal_i(buf_stream.size, 6);
  memset(str3, 0, sizeof(str3));
  n = cac_ostream_write(stream, (uint8_t*)str3, sizeof(str3));
  total += n;
  cl_assert_equal_i(n, 2048);
  cl_assert(buf_stream.capacity >= total);
}
