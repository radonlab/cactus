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
  cl_assert(n == 5);
  n = cac_istream_read(s, (uint8_t*)buf, sizeof(buf));
  cl_assert(n == 4);
}

void test_base__buf_stream__write() {}
