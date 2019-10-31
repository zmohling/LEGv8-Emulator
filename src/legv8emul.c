#include <stdint.h>
#include <stdio.h>

#include "instruction_impl.h"
#include "reader.h"

uint64_t X[512];         // main memory
uint64_t stack[64];      // stack
uint32_t* instructions;  // all instructions

/*
Print out the usage for this program
*/
void usage() { printf("./legv8emul <assembled legv8asm .machine file>"); }

void DEBUG_print_bits(uint32_t num) {
  for (int i = (32) - 1; i >= 0; i--) {
    printf("%d", (num >> i) & 0x1);
  }
  printf("\n");
}

int main(int argc, char* argv[]) {
  uint32_t* instructions;

  if (argc == 2) {
    // create uint32_t array of instructions
    instructions = read_instructions(argv[1]);

#ifdef DEBUG_MODE
    // Print bits of each instruction
    for (int i = 0; instructions[i]; i++) {
      DEBUG_print_bits(instructions[i]);
    }
#endif

  } else {
    usage();
  }

  // ADDI(X, 8, 8, 2);
  // ADDI(X, 9, 9, 1);

  // AND(X, 10, 9, 8);

  // printf("result: %lu\n", X[10]);
  //
  return 0;
}
