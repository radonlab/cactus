#include "base/buf_stream.h"

#define ENLARGE_CAP(x) (x + x >> 1)

static size_t buf_istream_read(cac_buf_istream_t* stream, uint8_t* buf, size_t len) { return len; }

static bool buf_istream_seek(cac_buf_istream_t* stream, size_t pos) { return true; }

static size_t buf_ostream_write(cac_buf_ostream_t* stream, const uint8_t* buf, size_t len) { return len; }

static cac_istream_ops_t buf_istream_ops = {
    &buf_istream_read,
    &buf_istream_seek,
    NULL,
};

static cac_ostream_ops_t buf_ostream_ops = {
    &buf_ostream_write,
    NULL,
    NULL,
};

cac_istream_t* cac_buf_istream_init(cac_buf_istream_t* stream, const uint8_t* buf, size_t size) {
  stream->base.ops = &buf_istream_ops;
}

cac_ostream_t* cac_buf_ostream_init(cac_buf_ostream_t* stream) {
  stream->base.ops = &buf_ostream_ops;
}
