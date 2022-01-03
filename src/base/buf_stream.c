#include "base/buf_stream.h"

#include <stdio.h>
#include <string.h>

#include "base/common.h"

#define DEFAULT_CAPACITY 256
#define ENLARGE_CAPACITY(x) (x + ((x + 1) >> 1))

static size_t buf_istream_read(cac_istream_t* stream, uint8_t* buf, size_t len) {
  cac_buf_istream_t* buf_stream = (cac_buf_istream_t*)stream;
  if (len == 0) {
    return 0;
  }
  if (buf_stream->offset >= buf_stream->size) {
    // underflowed
    return 0;
  }
  // copy left n bytes at most
  size_t count = buf_stream->size - buf_stream->offset;
  if (len < count) {
    count = len;
  }
  memcpy(buf, buf_stream->buf + buf_stream->offset, count);
  // forward offset
  buf_stream->offset += count;
  return count;
}

static bool buf_istream_seek(cac_istream_t* stream, size_t off, int whence) {
  cac_buf_istream_t* buf_stream = (cac_buf_istream_t*)stream;
  if (whence == SEEK_SET) {
    buf_stream->offset = off;
  } else if (whence == SEEK_CUR) {
    buf_stream->offset += off;
  } else if (whence == SEEK_END) {
    buf_stream->offset = buf_stream->size + off;
  } else {
    // invalid whence
    return false;
  }
  return true;
}

static void buf_ostream_ensure_capacity(cac_buf_ostream_t* buf_stream, size_t min_capacity) {
  if (min_capacity > buf_stream->capacity) {
    size_t new_capacity = ENLARGE_CAPACITY(buf_stream->capacity);
    if (new_capacity < min_capacity) {
      new_capacity = min_capacity;
    }
    buf_stream->buf = cac_realloc(buf_stream->buf, new_capacity);
    buf_stream->capacity = new_capacity;
  }
}

static size_t buf_ostream_write(cac_ostream_t* stream, const uint8_t* buf, size_t len) {
  cac_buf_ostream_t* buf_stream = (cac_buf_ostream_t*)stream;
  size_t newsize = buf_stream->size + len;
  if (buf_stream->max_size != 0 && newsize > buf_stream->max_size) {
    newsize = buf_stream->max_size;
    len = newsize - buf_stream->size;
  }
  buf_ostream_ensure_capacity(buf_stream, newsize);
  memcpy(buf_stream->buf + buf_stream->size, buf, len);
  // accumulate size
  buf_stream->size += len;
  return len;
}

static bool buf_ostream_close(cac_ostream_t* stream) {
  cac_buf_ostream_t* buf_stream = (cac_buf_ostream_t*)stream;
  cac_free(buf_stream->buf);
  return true;
}

static cac_istream_ops_t buf_istream_ops = {
    &buf_istream_read,
    &buf_istream_seek,
    NULL,
};

static cac_ostream_ops_t buf_ostream_ops = {
    &buf_ostream_write,
    NULL,
    &buf_ostream_close,
};

cac_istream_t* cac_buf_istream_init(cac_buf_istream_t* stream, const uint8_t* buf, size_t size) {
  stream->base.ops = &buf_istream_ops;
  stream->buf = buf;
  stream->size = size;
  stream->offset = 0;
  return (cac_istream_t*)stream;
}

cac_ostream_t* cac_buf_ostream_init(cac_buf_ostream_t* stream, size_t max_size) {
  stream->base.ops = &buf_ostream_ops;
  stream->buf = cac_malloc(DEFAULT_CAPACITY);
  stream->size = 0;
  stream->capacity = DEFAULT_CAPACITY;
  stream->max_size = max_size;
  return (cac_ostream_t*)stream;
}
