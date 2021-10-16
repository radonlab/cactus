#ifndef CACTUS_BASE_STREAM_H_
#define CACTUS_BASE_STREAM_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct cac_istream_ops_t cac_istream_ops_t;
typedef struct cac_ostream_ops_t cac_ostream_ops_t;

/**
 * Input stream
 */
typedef struct cac_istream_t {
  const cac_istream_ops_t* ops;
} cac_istream_t;

/**
 * Output stream
 */
typedef struct cac_ostream_t {
  const cac_ostream_ops_t* ops;
} cac_ostream_t;

/**
 * Input stream operations
 */
struct cac_istream_ops_t {
  size_t (*read)(cac_istream_t* stream, uint8_t* buf, size_t len);
  bool (*seek)(cac_istream_t* stream, size_t off, int whence);
  bool (*close)(cac_istream_t* stream);
};

/**
 * Output stream operations
 */
struct cac_ostream_ops_t {
  size_t (*write)(cac_ostream_t* stream, const uint8_t* buf, size_t len);
  bool (*flush)(cac_ostream_t* stream);
  bool (*close)(cac_ostream_t* stream);
};

// Input stream methods

size_t cac_istream_read(cac_istream_t* stream, uint8_t* buf, size_t len);
bool cac_istream_seek(cac_istream_t* stream, size_t off, int whence);
bool cac_istream_close(cac_istream_t* stream);

// Output stream methods

size_t cac_ostream_write(cac_ostream_t* stream, const uint8_t* buf, size_t len);
bool cac_ostream_flush(cac_ostream_t* stream);
bool cac_ostream_close(cac_ostream_t* stream);

#endif  // CACTUS_BASE_STREAM_H_
