#ifndef CACTUS_BASE_BUF_STREAM_H_
#define CACTUS_BASE_BUF_STREAM_H_

#include "stream.h"

#define BUF_STREAM_INIT_CAP 0x400

/**
 * Buffer input stream
 */
typedef struct cactus_buf_istream_t {
  cactus_istream_t base;
  uint8_t* buf;
  size_t size;
  size_t offset;
} cactus_buf_istream_t;

/**
 * Buffer output stream
 */
typedef struct cactus_buf_ostream_t {
  cactus_ostream_t base;
  uint8_t* buf;
  size_t size;
  size_t capacity;
} cactus_buf_ostream_t;

cactus_istream_t* cactus_buf_istream_init(cactus_buf_istream_t* stream, const uint8_t* buf, size_t size);

cactus_ostream_t* cactus_buf_ostream_init(cactus_buf_ostream_t* stream);

#endif  // CACTUS_BASE_BUF_STREAM_H_
