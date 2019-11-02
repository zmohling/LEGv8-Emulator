#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "debug.h"
#include "instruction_impl.h"
#include "parser.h"
#include "reader.h"

#define MAIN_MEMORY_SIZE 512
#define STACK_SIZE 64
#define REG_SIZE 32

uint64_t X[REG_SIZE];        // registers
uint64_t stack[STACK_SIZE];  // stack
uint64_t main_mem[512];      // main memory
uint32_t* instructions;      // all instructions

/*
Print out the usage for this program
*/
void usage() {
  printf("USAGE: ./legv8emul <assembled legv8asm .machine file>\n");
}

int main(int argc, char* argv[]) {
  uint32_t* instructions;

  if (argc == 2) {
    // create uint32_t array of instructions
    instructions = read_instructions(argv[1]);

#ifdef DEBUG_MODE
    // Print bits of each instruction
    for (int i = 0; instructions[i]; i++) {
      printf("%s\n", DEBUG_bits(instructions[i]));
      instruction_t instruction = parse(&instructions[i]);
      // instruction.func_ptr(X, &instruction);
    }

#endif

  } else {
    usage();
    return 0;
  }

  for (int i = 0; i < 32; i++) {
    ADDI(X, i, i, i * 10000);
  }
  // ADDI(X, 9, 9, 1);
  // DUMP(X, REG_SIZE, stack, STACK_SIZE);

  // printf("%d\n", (int)X[9]);
  // AND(X, 10, 9, 8);

  // printf("result: %lu\n", X[10]);
  //
  return 0;
}
