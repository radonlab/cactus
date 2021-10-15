#include "buf_stream.h"

#define ENLARGE_CAP(x) (x + x >> 1)

static size_t buf_istream_read(cactus_buf_istream_t* stream, uint8_t* buf, size_t len) { return len; }

static bool buf_istream_seek(cactus_buf_istream_t* stream, size_t pos) { return true; }

static size_t buf_ostream_write(cactus_buf_ostream_t* stream, const uint8_t* buf, size_t len) { return len; }

static cactus_istream_ops_t buf_istream_ops = {
    &buf_istream_read,
    &buf_istream_seek,
    NULL,
};

static cactus_ostream_ops_t buf_ostream_ops = {
    &buf_ostream_write,
    NULL,
    NULL,
};

cactus_istream_t* cactus_buf_istream_init(cactus_buf_istream_t* stream, const uint8_t* buf, size_t size) {
  stream->base.ops = &buf_istream_ops;
}

cactus_ostream_t* cactus_buf_ostream_init(cactus_buf_ostream_t* stream) {
  stream->base.ops = &buf_ostream_ops;
}
