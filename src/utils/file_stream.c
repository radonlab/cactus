#include "file_stream.h"

#define FILE_BUFFER_SIZE 0x2000

static size_t file_istream_read(cactus_file_istream_t* stream, uint8_t* buf, size_t len) {
  return fread(buf, sizeof(uint8_t), len, stream->file);
}

static bool file_istream_seek(cactus_file_istream_t* stream, size_t pos) {
  int ret = fseek(stream->file, pos, SEEK_SET);
  return !ret;
}

static bool file_istream_close(cactus_file_istream_t* stream) {
  int ret = fclose(stream->file);
  return !ret;
}

static size_t file_ostream_write(cactus_file_ostream_t* stream, const uint8_t* buf, size_t len) {
  return fwrite(buf, sizeof(uint8_t), len, stream->file);
}

static bool file_ostream_flush(cactus_file_ostream_t* stream) {
  int ret = fflush(stream->file);
  return !ret;
}

static bool file_ostream_close(cactus_file_ostream_t* stream) {
  int ret = fclose(stream->file);
  return !ret;
}

static cactus_istream_ops_t file_istream_ops = {
    &file_istream_read,
    &file_istream_seek,
    &file_istream_close,
};

static cactus_ostream_ops_t file_ostream_ops = {
    &file_ostream_write,
    &file_ostream_flush,
    &file_ostream_close,
};

cactus_istream_t* cactus_file_istream_init(cactus_file_istream_t* stream, FILE* file) {
  stream->base.ops = &file_istream_ops;
  stream->file = file;
  setvbuf(file, NULL, _IOFBF, FILE_BUFFER_SIZE);
  return stream;
}

cactus_ostream_t* cactus_file_ostream_init(cactus_file_ostream_t* stream, FILE* file) {
  stream->base.ops = &file_ostream_ops;
  stream->file = file;
  setvbuf(file, NULL, _IOFBF, FILE_BUFFER_SIZE);
  return stream;
}
