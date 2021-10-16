#include <assert.h>
#include <stdlib.h>

void handle_out_of_memory() {
  abort();
}

void* cac_malloc(size_t size) {
  assert(size != 0);
  void* ptr = malloc(size);
  if (!ptr) {
    handle_out_of_memory();
  }
  return ptr;
}

void* cac_calloc(size_t size) {
  assert(size != 0);
  void* ptr = calloc(1, size);
  if (!ptr) {
    handle_out_of_memory();
  }
  return ptr;
}

void* cac_realloc(void* ptr, size_t size) {
  assert(size != 0);
  void* newptr = realloc(ptr, size);
  if (!newptr) {
    handle_out_of_memory();
  }
  return newptr;
}

void cac_free(void* ptr) {
  free(ptr);
}
