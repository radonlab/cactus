#include "stream.h"

size_t cactus_istream_read(cactus_istream_t* stream, uint8_t buf[], size_t len) {
  return stream->ops->read(stream, buf, len);
}

bool cactus_istream_close(cactus_istream_t* stream) {
  return stream->ops->close(stream);
}

size_t cactus_ostream_write(cactus_ostream_t* stream, const uint8_t* buf, size_t len) {
  return stream->ops->write(stream, buf, len);
}

bool cactus_ostream_close(cactus_ostream_t* stream) {
  return stream->ops->close(stream);
}
