#ifndef CACTUS_UTILS_STREAM_H_
#define CACTUS_UTILS_STREAM_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct cactus_istream_ops_t cactus_istream_ops_t;
typedef struct cactus_ostream_ops_t cactus_ostream_ops_t;

/**
 * Input stream
 */
typedef struct cactus_istream_t {
  const cactus_istream_ops_t* ops;
} cactus_istream_t;

/**
 * Output stream
 */
typedef struct cactus_ostream_t {
  const cactus_ostream_ops_t* ops;
} cactus_ostream_t;

struct cactus_istream_ops_t {
  size_t (*read)(cactus_istream_t* stream, uint8_t* buf, size_t len);
  bool (*close)(cactus_istream_t* stream);
};

struct cactus_ostream_ops_t {
  size_t (*write)(cactus_ostream_t* stream, const uint8_t* buf, size_t len);
  bool (*close)(cactus_ostream_t* stream);
};

size_t cactus_istream_read(cactus_istream_t* stream, uint8_t* buf, size_t len);
bool cactus_istream_close(cactus_istream_t* stream);

size_t cactus_ostream_write(cactus_ostream_t* stream, const uint8_t* buf,
                            size_t len);
bool cactus_ostream_close(cactus_ostream_t* stream);

// size_t cactus_ostream_write(cactus_stream_t* stream, uint8_t* buf, size_t
// len); void cactus_ostream_flush(cactus_stream_t* stream); bool
// cactus_ostream_close(cactus_stream_t* stream);

#endif  // CACTUS_UTILS_STREAM_H_
