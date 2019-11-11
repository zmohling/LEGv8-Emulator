#include "disassembler.h"

#include <stdio.h>
#include <string.h>

#include "instruction_impl.h"
#include "parser.h"

static instruction_stack_t *stack;

void log_instruction(instruction_t *instr) {
  if (!stack) {
    stack = malloc(sizeof(instruction_stack_t));
  }

  stack_node_t *new_head = malloc(sizeof(stack_node_t));
  new_head->instr = *instr;

  if (!stack->head) {
    stack->head = new_head;
  } else {
    new_head->prev = stack->head;
    stack->head = new_head;
  }
}

static char *get_instr_string(instruction_t *instr) {
  void (*func)(machine_state_t *, instruction_t *) = instr->instruction_func;
  char *result = NULL, *func_name = NULL;

  if (func == ADD) func_name = strdup("ADD");
  if (func == ADDI) func_name = strdup("ADDI");
  if (func == AND) func_name = strdup("AND");
  if (func == ANDI) func_name = strdup("ANDI");
  if (func == B) func_name = strdup("B");

  if (func == B_COND) func_name = strdup("B.cond");

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
    asprintf(&result, "%s %d", func_name, instr->B.BR_address);

  if (instr->format == format_CB)
    asprintf(&result, "%s %u, %d", func_name, instr->CB.Rt,
             instr->CB.COND_BR_address);

  return result;
}

static void traverse_call_stack(stack_node_t *head) {
  if (head->prev != NULL) {
    traverse_call_stack(head->prev);
  }

  printf("%s\n", get_instr_string(&head->instr));
}

void print_disassembled() {
  printf("\nDISASSEMBLED PROGRAM:\n");

  traverse_call_stack(stack->head);
}
