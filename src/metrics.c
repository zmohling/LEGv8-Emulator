#include <stdbool.h>
#include <stdio.h>

#include "instruction_impl.h"
#include "parser.h"

static unsigned int num_cycles_unpipelined;
static unsigned int num_cycles_pipelined = 4;
static unsigned int num_data_hazards;
static unsigned int num_control_hazards;
static unsigned int num_cycles_pipelined_with_bypassing = 4;

/* Return num additional cycles */
static void handle_data_hazard(instruction_t* instr) {
  static instruction_t ex, mem;

  for (int i = 0; i < 2; i++) {
    instruction_t* prev_instr = (i == 0) ? &ex : &mem;

    if (prev_instr == NULL) continue;

    bool reg_write = (prev_instr->format == format_R) ||
                     (prev_instr->format == format_I) ||
                     (prev_instr->instruction_func == LDUR);

    /* Hazard condition */
    if ((reg_write) && (prev_instr->R.Rd != 31) &&
        ((prev_instr->R.Rd == instr->R.Rn) ||
         (prev_instr->R.Rd == instr->R.Rm))) {
      if (prev_instr->instruction_func == LDUR) {
        num_cycles_pipelined += (2 - i);
        num_cycles_pipelined_with_bypassing += (1 - i);
      } else {
        num_cycles_pipelined += (2 - i);
      }

      num_data_hazards++;
    }
  }

  mem = ex;
  ex = *instr;
}

static void handle_control_hazard(instruction_t* instr) {
  if (instr->format == format_CB) {
    num_cycles_pipelined += 3;
    num_cycles_pipelined_with_bypassing += 3;

    num_control_hazards++;
  }
}

void analyze_instruction(instruction_t* instr) {
  /* Unpipelined */
  num_cycles_unpipelined += 1;

  /* Pipelined */
  handle_data_hazard(instr);
  handle_control_hazard(instr);

  num_cycles_pipelined++;
  num_cycles_pipelined_with_bypassing++;
}

void print_statistics() {
  printf("\nSTATISTICS:\n");
  printf("Number of cycles (unpipelined): %u (%u)\n", num_cycles_unpipelined,
         num_cycles_unpipelined * 5);
  printf("Number of cycles (pipelined): %u\n", num_cycles_pipelined);
  printf("Number of data hazards: %u\n", num_data_hazards);
  printf("Number of control hazards: %u\n", num_control_hazards);
  printf("Number of cycles (pipelined w/ bypassing): %u\n",
         num_cycles_pipelined_with_bypassing);
}
