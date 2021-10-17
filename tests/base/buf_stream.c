#include "base/buf_stream.h"

#include <string.h>

#include "tests.h"

void test_base__buf_stream__read() {
  char* str = "foobarbaz";
  char buf[5];
  size_t n;
  cac_buf_istream_t bs;
  cac_buf_istream_init(&bs, (uint8_t*)str, strlen(str));
  cac_istream_t* s = (cac_istream_t*)&bs;
  n = cac_istream_read(s, (uint8_t*)buf, sizeof(buf));
  cl_assert_equal_i(n, 5);
  cl_assert_equal_strn(buf, "fooba", n);
  n = cac_istream_read(s, (uint8_t*)buf, sizeof(buf));
  cl_assert_equal_i(n, 4);
  cl_assert_equal_strn(buf, "rbaz", n);
  n = cac_istream_read(s, (uint8_t*)buf, 1);
  cl_assert_equal_i(n, 0);
  cl_assert_equal_i(bs.offset, bs.size);
}

void test_base__buf_stream__write() {
  char* str1 = "foo";
  char* str2 = "bar";
  size_t n;
  cac_buf_ostream_t bs;
  cac_buf_ostream_init(&bs);
  cac_ostream_t* s = (cac_ostream_t*)&bs;
  n = cac_ostream_write(s, (uint8_t*)str1, strlen(str1));
  cl_assert_equal_i(n, 3);
  n = cac_ostream_write(s, (uint8_t*)str2, strlen(str2));
  cl_assert_equal_i(n, 3);
  cl_assert_equal_i(bs.size, 6);
}
