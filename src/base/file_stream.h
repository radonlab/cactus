#ifndef CACTUS_BASE_FILE_STREAM_H_
#define CACTUS_BASE_FILE_STREAM_H_

#include <stdio.h>

#include "base/stream.h"

/**
 * File input stream
 */
typedef struct cac_file_istream_t {
  cac_istream_t base;
  FILE* file;
} cac_file_istream_t;

/**
 * File output stream
 */
typedef struct cac_file_ostream_t {
  cac_ostream_t base;
  FILE* file;
} cac_file_ostream_t;

cac_istream_t* cac_file_istream_init(cac_file_istream_t* stream, FILE* file);

cac_ostream_t* cac_file_ostream_init(cac_file_ostream_t* stream, FILE* file);

#endif  // CACTUS_BASE_FILE_STREAM_H_
