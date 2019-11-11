#ifndef DISASSEMBLER_H_
#define DISASSEMBLER_H_

#include "parser.h"

typedef struct stack_node stack_node_t;
typedef struct stack_node {
  stack_node_t *prev;
  instruction_t instr;
} stack_node_t;

typedef struct instruction_stack {
  stack_node_t *head;
} instruction_stack_t;

void log_instruction(instruction_t *);
void print_disassembled();

#endif
