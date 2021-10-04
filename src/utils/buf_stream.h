#ifndef CACTUS_UTILS_BUF_STREAM_H_
#define CACTUS_UTILS_BUF_STREAM_H_

#include "stream.h"

/**
 * Buffer input stream
 */
typedef struct cactus_buf_istream_t {
  cactus_istream_t base;
} cactus_buf_istream_t;

/**
 * Buffer output stream
 */
typedef struct cactus_buf_ostream_t {
  cactus_ostream_t base;
} cactus_buf_ostream_t;

cactus_istream_t* cactus_buf_istream_init(cactus_buf_istream_t* stream, const uint8_t* buf, size_t size);

cactus_ostream_t* cactus_buf_ostream_init(cactus_buf_ostream_t* stream, size_t size);

#endif  // CACTUS_UTILS_BUF_STREAM_H_
