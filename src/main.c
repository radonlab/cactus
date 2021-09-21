#include "cactus/cactus.h"

#include <stdio.h>

#include "parser/grammar.h"

int main(int argc, char* argv[]) {
  cactus_context_t* ctx = cactus_create(NULL);
  cactus_parse(ctx, NULL);
  cactus_destroy(ctx);
  return 0;
}
