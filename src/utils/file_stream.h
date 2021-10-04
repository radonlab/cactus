#ifndef CACTUS_UTILS_FILE_STREAM_H_
#define CACTUS_UTILS_FILE_STREAM_H_

#include <stdio.h>

#include "stream.h"

/**
 * File input stream
 */
typedef struct cactus_file_istream_t {
  cactus_istream_t base;
  FILE* file;
} cactus_file_istream_t;

/**
 * File output stream
 */
typedef struct cactus_file_ostream_t {
  cactus_ostream_t base;
  FILE* file;
} cactus_file_ostream_t;

cactus_istream_t* cactus_file_istream_init(cactus_file_istream_t* stream, FILE* file);

cactus_ostream_t* cactus_file_ostream_init(cactus_file_ostream_t* stream, FILE* file);

#endif  // CACTUS_UTILS_FILE_STREAM_H_
