#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "legv8emul.h"
#include "debug.h"
#include "instruction_impl.h"
#include "parser.h"
#include "reader.h"

machine_state_t machine_state;

/*
Print out the usage for this program
*/
void usage() {
  printf("USAGE: ./legv8emul <assembled legv8asm .machine file>\n");
}

int main(int argc, char* argv[]) {

  if (argc == 2) {
    // create uint32_t array of instructions
    machine_state.instructions = read_instructions(argv[1]);

#ifdef DEBUG_MODE
    // Print bits of each instruction
    for (int i = 0; instructions[i]; i++) {
      printf("%s\n", DEBUG_bits(instructions[i]));

      /* Parse Instruction */
      instruction_t instruction = parse(&instructions[i]);

      /* Execute Instruction */
      instruction.instruction_func(X, &instruction);
    }

#endif

  } else {
    usage();
    return 0;
  }

  for (int i = 0; i < 32; i++) {
    //ADDI(X, i, i, i * 10000);
  }
  // ADDI(X, 9, 9, 1);
  // DUMP(X, REG_SIZE, stack, STACK_SIZE);

  // printf("%d\n", (int)X[9]);
  // AND(X, 10, 9, 8);

  // printf("result: %lu\n", X[10]);
  //
  return 0;
}
