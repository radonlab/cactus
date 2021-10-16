#include "base/buf_stream.h"

#include "base/common.h"

#define ENLARGE_CAP(x) (x + x >> 1)

static size_t buf_istream_read(cac_buf_istream_t* stream, uint8_t* buf, size_t len) { return len; }

static bool buf_istream_seek(cac_buf_istream_t* stream, size_t pos, int whence) {

static size_t buf_ostream_write(cac_buf_ostream_t* stream, const uint8_t* buf, size_t len) { return len; }

static bool buf_ostream_flush(cac_buf_ostream_t* stream) {
  return true;
}

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

cac_ostream_t* cac_buf_ostream_init(cac_buf_ostream_t* stream) {
  stream->base.ops = &buf_ostream_ops;
  stream->buf = cac_malloc(BUF_STREAM_INIT_CAP);
  stream->size = 0;
  stream->capacity = BUF_STREAM_INIT_CAP;
}
