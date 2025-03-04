#include "disassembler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "instruction_impl.h"
#include "legv8emul.h"
#include "parser.h"

static char *get_instr_string(instruction_t *instr) {
  void (*func)(machine_state_t *, instruction_t *) = instr->instruction_func;
  char *result, *func_name = "";

  if (func == ADD) func_name = strdup("ADD");
  if (func == ADDI) func_name = strdup("ADDI");
  if (func == AND) func_name = strdup("AND");
  if (func == ANDI) func_name = strdup("ANDI");
  if (func == B) func_name = strdup("B");
  if (func == BL) func_name = strdup("BL");
  if (func == BR) func_name = strdup("BR");
  if (func == CBNZ) func_name = strdup("CBNZ");
  if (func == CBZ) func_name = strdup("CBZ");
  if (func == DUMP) func_name = strdup("DUMP");
  if (func == EOR) func_name = strdup("EOR");
  if (func == EORI) func_name = strdup("EORI");
  if (func == LDUR) func_name = strdup("LDUR");
  if (func == HALT) func_name = strdup("HALT");
  if (func == LSL) func_name = strdup("LSL");
  if (func == LSR) func_name = strdup("LSR");
  if (func == MUL) func_name = strdup("MUL");
  if (func == ORR) func_name = strdup("ORR");
  if (func == ORRI) func_name = strdup("ORRI");
  if (func == PRNL) func_name = strdup("PRNL");
  if (func == PRNT) func_name = strdup("PRNT");
  if (func == STUR) func_name = strdup("STUR");
  if (func == SUB) func_name = strdup("SUB");
  if (func == SUBI) func_name = strdup("SUBI");
  if (func == SUBIS) func_name = strdup("SUBIS");
  if (func == SUBS) func_name = strdup("SUBS");
  if (func == UDIV) func_name = strdup("UDIV");

  // clang-format off
  if (func == B_COND){
    switch(instr->CB.Rt){
      case EQ: func_name = strdup("B.EQ"); break;
      case NE: func_name = strdup("B.NE"); break;
      case HS: func_name = strdup("B.HS"); break;
      case LO: func_name = strdup("B.LO"); break;
      case MI: func_name = strdup("B.MI"); break;
      case PL: func_name = strdup("B.PL"); break;
      case VS: func_name = strdup("B.VS"); break;
      case VC: func_name = strdup("B.VC"); break;
      case HI: func_name = strdup("B.HI"); break;
      case LS: func_name = strdup("B.LS"); break;
      case GE: func_name = strdup("B.GE"); break;
      case LT: func_name = strdup("B.LT"); break;
      case GT: func_name = strdup("B.GT"); break;
      case LE: func_name = strdup("B.LE"); break;
    }
  }
  // clang-format on

  if (instr->format == format_R)
    asprintf(&result, "%s X%u, X%u, X%u", func_name, instr->R.Rd, instr->R.Rn,
             instr->R.Rm);

  if (instr->format == format_I)
    asprintf(&result, "%s X%u, X%u, #%u", func_name, instr->I.Rd, instr->I.Rn,
             instr->I.ALU_immediate);

  if (instr->format == format_D)
    asprintf(&result, "%s X%u, [X%u, #%u]", func_name, instr->D.Rt, instr->D.Rn,
             instr->D.DT_address);

  if (instr->format == format_B)
    asprintf(&result, "%s %d", func_name,
             ((int32_t)((instr->B.BR_address) << 6)) >> 6);

  if (instr->format == format_CB)
    asprintf(&result, "%s X%u, %d", func_name, instr->CB.Rt,
             instr->CB.COND_BR_address);

  return result;
}

void disassemble(machine_state_t *machine_state) {
  printf("\nDISASSEMBLED PROGRAM:\n");

  for (int i = 0; i < machine_state->num_instructions; i++) {
    instruction_t instr = parse(&(machine_state->instructions[i]));
    printf("%s\n", get_instr_string(&instr));
  }
}
