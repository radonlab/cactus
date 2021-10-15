#include "stream.h"

size_t cac_istream_read(cac_istream_t* stream, uint8_t buf[], size_t len) {
  return stream->ops->read(stream, buf, len);
}

bool cac_istream_seek(cac_istream_t* stream, size_t pos) { return stream->ops->seek(stream, pos); }

bool cac_istream_close(cac_istream_t* stream) { return stream->ops->close(stream); }

size_t cac_ostream_write(cac_ostream_t* stream, const uint8_t* buf, size_t len) {
  return stream->ops->write(stream, buf, len);
}

bool cac_ostream_flush(cac_ostream_t* stream) { return stream->ops->flush(stream); }

bool cac_ostream_close(cac_ostream_t* stream) { return stream->ops->close(stream); }
