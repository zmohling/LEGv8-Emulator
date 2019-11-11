#include "legv8emul.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "debug.h"
#include "disassembler.h"
#include "instruction_impl.h"
#include "metrics.h"
#include "parser.h"
#include "reader.h"

machine_state_t machine_state;

/*
Print out the usage for this program
*/
void usage() {
  printf("USAGE: ./legv8emul <assembled legv8asm .machine file>\n");
}

void setup(machine_state_t* machine_state) {
  machine_state->X[SP] = STACK_SIZE;
  machine_state->X[FP] = STACK_SIZE;
  machine_state->X[XZR] = 0;
  machine_state->X[PC] = 0;
}

int main(int argc, char* argv[]) {
  if (argc == 2) {
    setup(&machine_state);

    unsigned long long num_instructions = 0;
    machine_state.instructions = read_instructions(argv[1], &num_instructions);

#ifdef DEBUG_MODE
//    // Print bits of each instruction
//    for (int i = 0; machine_state.instructions[i]; i++) {
//      printf("%s\n", DEBUG_bits(machine_state.instructions[i]));
//
//      /* Parse Instruction */
//      instruction_t instruction = parse(&machine_state.instructions[i]);
//
//      /* Execute Instruction */
//      instruction.instruction_func(&machine_state, &instruction);
//    }
#endif

    // for (int i = 0; i < num_instructions; i++) {
    //   /* Parse Instruction */
    //   instruction_t instruction = parse(&machine_state.instructions[i]);

<<<<<<< HEAD
    //   /* Log and analyze */
    //   analyze_instruction(&instruction);

    //   /* Execute Instruction */
    //   instruction.instruction_func(&machine_state, &instruction);
    // }
    printf("Total instructions: %llu\n", num_instructions);
    if(num_instructions > 0){
      while((int)(machine_state.X[PC] / 4) > -1){
        printf("PC: %ld\n", machine_state.X[PC] / 4);
        /* Parse Instruction */
        instruction_t instruction = parse(&machine_state.instructions[machine_state.X[PC] / 4]);

        /* Log and analyze */
        analyze_instruction(&instruction);

        /* Execute Instruction */
        instruction.instruction_func(&machine_state, &instruction);

        machine_state.X[PC] = machine_state.X[PC] + 4;

        if(machine_state.X[PC] / 4 >= num_instructions && instruction.format != format_B){
          break;
        }
      }
=======
      /* Log to metrics module */
      analyze_instruction(&instruction);

      /* Log to disassembler module */
      log_instruction(&instruction);

      /* Execute Instruction */
      instruction.instruction_func(&machine_state, &instruction);
>>>>>>> 0998aa8a6c95a03479266a8432592eb2542e9617
    }

  } else {
    usage();
    return 0;
  }

  DUMP(&machine_state, NULL);

  /* Print metrics */
  print_statistics();

  print_disassembled();

  return 0;
}
