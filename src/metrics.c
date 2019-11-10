#include <stdbool.h>
#include <stdio.h>

#include "instruction_impl.h"
#include "parser.h"

static unsigned int num_cycles_unpipelined;
static unsigned int num_cycles_pipelined = 4;
static unsigned int num_data_hazards;
static unsigned int num_control_hazards;
static unsigned int num_cycles_pipelined_with_bypassing;

/* Return num additional cycles */
static void handle_data_hazard(instruction_t* instr) {
  static instruction_t *ex, *mem;

  for (int i = 0; i < 2; i++) {
    instruction_t* prev_instr = (i == 0) ? ex : mem;

    if (prev_instr == NULL) continue;

    bool reg_write = (prev_instr->format == format_D) ||
                     (prev_instr->format == format_I) ||
                     (prev_instr->instruction_func == LDUR);

    /* Hazard condition */
    if ((reg_write) && (prev_instr->R.Rd != 31) &&
        ((prev_instr->R.Rd == instr->R.Rn) ||
         (prev_instr->R.Rd == instr->R.Rm))) {
      num_cycles_pipelined += (2 - i);
    }
  }

  mem = ex;
  ex = instr;
}

void analyze_instruction(instruction_t* instr) {
  /* Unpipelined */
  num_cycles_unpipelined += 1;

  /* Pipelined */
  handle_data_hazard(instr);
  num_cycles_pipelined++;
}

void print_statistics() {
  /* */
  printf("Number of cycles (unpipelined): %u\n", num_cycles_unpipelined);
  printf("Number of cycles (pipelined): %u\n", num_cycles_pipelined);
}
