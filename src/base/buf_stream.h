#ifndef CACTUS_BASE_BUF_STREAM_H_
#define CACTUS_BASE_BUF_STREAM_H_

#include "base/stream.h"

/**
 * Buffer input stream
 */
typedef struct cac_buf_istream_t {
  cac_istream_t base;
  uint8_t* buf;
  size_t size;
  size_t offset;
} cac_buf_istream_t;

/**
 * Buffer output stream
 */
typedef struct cac_buf_ostream_t {
  cac_ostream_t base;
  uint8_t* buf;
  size_t size;
  size_t capacity;
  size_t max_size;
} cac_buf_ostream_t;

cac_istream_t* cac_buf_istream_init(cac_buf_istream_t* stream, const uint8_t* buf, size_t size);
cac_ostream_t* cac_buf_ostream_init(cac_buf_ostream_t* stream, size_t max_size);

#endif  // CACTUS_BASE_BUF_STREAM_H_
