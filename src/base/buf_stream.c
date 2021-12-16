#include "base/buf_stream.h"

#include <stdio.h>
#include <string.h>

#include "base/common.h"

#define DEFAULT_CAPACITY 256
#define ENLARGE_CAPACITY(x) (x + (x + 1 >> 1))

static size_t buf_istream_read(cac_buf_istream_t* stream, uint8_t* buf, size_t len) {
  if (len == 0) {
    return 0;
  }
  if (stream->offset >= stream->size) {
    // underflowed
    return 0;
  }
  // copy left n bytes at most
  size_t count = stream->size - stream->offset;
  if (len < count) {
    count = len;
  }
  memcpy(buf, stream->buf + stream->offset, count);
  // forward offset
  stream->offset += count;
  return count;
}

static bool buf_istream_seek(cac_buf_istream_t* stream, size_t off, int whence) {
  if (whence == SEEK_SET) {
    stream->offset = off;
  } else if (whence == SEEK_CUR) {
    stream->offset += off;
  } else if (whence == SEEK_END) {
    stream->offset = stream->size + off;
  } else {
    // invalid whence
    return false;
  }
  return true;
}

static bool buf_istream_close(cac_buf_istream_t* stream) { return true; }

static void buf_ostream_ensure_capacity(cac_buf_ostream_t* stream, size_t min_capacity) {
  if (min_capacity > stream->capacity) {
    size_t new_capacity = ENLARGE_CAPACITY(stream->capacity);
    if (new_capacity < min_capacity) {
      new_capacity = min_capacity;
    }
    stream->buf = cac_realloc(stream->buf, new_capacity);
    stream->capacity = new_capacity;
  }
}

static size_t buf_ostream_write(cac_buf_ostream_t* stream, const uint8_t* buf, size_t len) {
  size_t newsize = stream->size + len;
  if (stream->max_size != 0 && newsize > stream->max_size) {
    newsize = stream->max_size;
    len = newsize - stream->size;
  }
  buf_ostream_ensure_capacity(stream, newsize);
  memcpy(stream->buf + stream->size, buf, len);
  // accumulate size
  stream->size += len;
  return len;
}

static bool buf_ostream_flush(cac_buf_ostream_t* stream) { return true; }

static bool buf_ostream_close(cac_buf_ostream_t* stream) {
  cac_free(stream->buf);
  return true;
}

static cac_istream_ops_t buf_istream_ops = {
    &buf_istream_read,
    &buf_istream_seek,
    &buf_istream_close,
};

static cac_ostream_ops_t buf_ostream_ops = {
    &buf_ostream_write,
    &buf_ostream_flush,
    &buf_ostream_close,
};

cac_istream_t* cac_buf_istream_init(cac_buf_istream_t* stream, const uint8_t* buf, size_t size) {
  stream->base.ops = &buf_istream_ops;
  stream->buf = buf;
  stream->size = size;
  stream->offset = 0;
}

cac_ostream_t* cac_buf_ostream_init(cac_buf_ostream_t* stream, size_t max_size) {
  stream->base.ops = &buf_ostream_ops;
  stream->buf = cac_malloc(DEFAULT_CAPACITY);
  stream->size = 0;
  stream->capacity = DEFAULT_CAPACITY;
  stream->max_size = max_size;
}
