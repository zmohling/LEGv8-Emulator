#include "debug.h"

#include <stdint.h>

char* DEBUG_bits(uint32_t num) {
  char* bits = (char*)malloc(33 * sizeof(char));
  bits[32] = '\0';

  for (int i = (32) - 1; i >= 0; i--) {
    bits[31 - i] = ((num >> i) & 0x1) + 48;
  }

  return bits;
}
