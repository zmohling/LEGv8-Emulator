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

uint32_t* read_instructions(const char* filepath) {
  FILE* f = fopen(filepath, "rb");
  int f_size = get_size(f) / 4;

  uint32_t* instructions = malloc(f_size * sizeof(uint32_t));

  for (int i = 0; i < f_size; i++) {
    uint32_t big_endian_word;

    if (!fread(&big_endian_word, sizeof(uint32_t), 1, f)) {
      fprintf(stderr, "Error (%d)\n", errno);
      exit(-1);
    }

    instructions[i] = be32toh(big_endian_word);
  }

  fclose(f);

  return instructions;
}
