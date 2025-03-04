#include "reader.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#include "../include/endian_wrapper.h"
#elif __linux__
#include <endian.h>
#endif

static unsigned int get_size(FILE* f) {
  fseek(f, 0, SEEK_END);  // seek to end of file
  int size = ftell(f);    // get current file pointer
  fseek(f, 0, SEEK_SET);  // seek back to beginning of file

  return size;
}

uint32_t* read_instructions(const char* filepath,
                            unsigned long long* num_instructions) {
  FILE* f = fopen(filepath, "rb");
  *num_instructions = get_size(f) / 4;

  uint32_t* instructions = malloc(*num_instructions * sizeof(uint32_t));

  clearerr(f);

  for (int i = 0; i < *num_instructions; i++) {
    uint32_t big_endian_word;

    if (!fread(&big_endian_word, sizeof(uint32_t), 1, f)) {
      if (feof(f)) break;

      fprintf(stderr, "Error (%d)\n", errno);
      exit(-1);
    }

    instructions[i] = be32toh(big_endian_word);
  }

  fclose(f);

  return instructions;
}
