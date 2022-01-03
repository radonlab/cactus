#include "base/file_stream.h"

#define FILE_BUFFER_SIZE 0x2000

static size_t file_istream_read(cac_istream_t* stream, uint8_t* buf, size_t len) {
  cac_file_istream_t* file_stream = (cac_file_istream_t*)stream;
  return fread(buf, sizeof(uint8_t), len, file_stream->file);
}

static bool file_istream_seek(cac_istream_t* stream, size_t off, int whence) {
  cac_file_istream_t* file_stream = (cac_file_istream_t*)stream;
  int ret = fseek(file_stream->file, off, whence);
  return !ret;
}

static bool file_istream_close(cac_istream_t* stream) {
  cac_file_istream_t* file_stream = (cac_file_istream_t*)stream;
  int ret = fclose(file_stream->file);
  return !ret;
}

static size_t file_ostream_write(cac_ostream_t* stream, const uint8_t* buf, size_t len) {
  cac_file_ostream_t* file_stream = (cac_file_ostream_t*)stream;
  return fwrite(buf, sizeof(uint8_t), len, file_stream->file);
}

static bool file_ostream_flush(cac_ostream_t* stream) {
  cac_file_ostream_t* file_stream = (cac_file_ostream_t*)stream;
  int ret = fflush(file_stream->file);
  return !ret;
}

static bool file_ostream_close(cac_ostream_t* stream) {
  cac_file_ostream_t* file_stream = (cac_file_ostream_t*)stream;
  int ret = fclose(file_stream->file);
  return !ret;
}

static cac_istream_ops_t file_istream_ops = {
    &file_istream_read,
    &file_istream_seek,
    &file_istream_close,
};

static cac_ostream_ops_t file_ostream_ops = {
    &file_ostream_write,
    &file_ostream_flush,
    &file_ostream_close,
};

cac_istream_t* cac_file_istream_open(cac_file_istream_t* stream, const char* path, const char* modes) {
  FILE* file = fopen(path, modes);
  return cac_file_istream_from(stream, file);
}

cac_ostream_t* cac_file_ostream_open(cac_file_ostream_t* stream, const char* path, const char* modes) {
  FILE* file = fopen(path, modes);
  return cac_file_ostream_from(stream, file);
}

cac_istream_t* cac_file_istream_from(cac_file_istream_t* stream, FILE* file) {
  stream->base.ops = &file_istream_ops;
  stream->file = file;
  setvbuf(file, NULL, _IOFBF, FILE_BUFFER_SIZE);
  return (cac_istream_t*)stream;
}

cac_ostream_t* cac_file_ostream_from(cac_file_ostream_t* stream, FILE* file) {
  stream->base.ops = &file_ostream_ops;
  stream->file = file;
  setvbuf(file, NULL, _IOFBF, FILE_BUFFER_SIZE);
  return (cac_ostream_t*)stream;
}
