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

/**
 * Input stream operations
 */
struct cactus_istream_ops_t {
  size_t (*read)(cactus_istream_t* stream, uint8_t* buf, size_t len);
  bool (*seek)(cactus_istream_t* stream, size_t pos);
  bool (*close)(cactus_istream_t* stream);
};

/**
 * Output stream operations
 */
struct cactus_ostream_ops_t {
  size_t (*write)(cactus_ostream_t* stream, const uint8_t* buf, size_t len);
  bool (*flush)(cactus_ostream_t* stream);
  bool (*close)(cactus_ostream_t* stream);
};

// Input stream methods

size_t cactus_istream_read(cactus_istream_t* stream, uint8_t* buf, size_t len);
bool cactus_istream_seek(cactus_istream_t* stream, size_t pos);
bool cactus_istream_close(cactus_istream_t* stream);

// Output stream methods

size_t cactus_ostream_write(cactus_ostream_t* stream, const uint8_t* buf, size_t len);
bool cactus_ostream_flush(cactus_ostream_t* stream);
bool cactus_ostream_close(cactus_ostream_t* stream);

#endif  // CACTUS_UTILS_STREAM_H_
