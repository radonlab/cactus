#ifndef CACTUS_BASE_COMMON_H_
#define CACTUS_BASE_COMMON_H_

#include <stddef.h>

/**
 * Allocate memory or panic
 */
void* cac_malloc(size_t size);

/**
 * Allocate memory and zero it or panic
 */
void* cac_calloc(size_t size);

/**
 * Reallocate memory or panic
 */
void* cac_realloc(void* ptr, size_t size);

/**
 * Free memory
 */
void cac_free(void* ptr);

#endif  // CACTUS_BASE_COMMON_H_
