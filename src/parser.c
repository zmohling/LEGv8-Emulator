#include "parser.h"

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "instruction_impl.h"

const uint32_t opcodes[37] = {
    OPCODE_ADD,    OPCODE_ADDI,  OPCODE_AND,    OPCODE_ANDI,  OPCODE_B,
    OPCODE_B_COND, OPCODE_BL,    OPCODE_BR,     OPCODE_CBNZ,  OPCODE_CBZ,
    OPCODE_DUMP,   OPCODE_EOR,   OPCODE_EORI,   OPCODE_HALT,  OPCODE_LDUR,
    OPCODE_LDURB,  OPCODE_LDURH, OPCODE_LDURSW, OPCODE_LSL,   OPCODE_LSR,
    OPCODE_MUL,    OPCODE_ORR,   OPCODE_ORRI,   OPCODE_PRNL,  OPCODE_PRNT,
    OPCODE_SDIV,   OPCODE_SMULH, OPCODE_STUR,   OPCODE_STURB, OPCODE_STURH,
    OPCODE_STURW,  OPCODE_SUB,   OPCODE_SUBI,   OPCODE_SUBIS, OPCODE_SUBS,
    OPCODE_UDIV,   OPCODE_UMULH};

static const struct {
  const uint32_t opcode;
  const instruction_format_t format;
} instruction_format_lookup[] = {
    {OPCODE_ADD, format_R},   {OPCODE_ADDI, format_I},
    {OPCODE_AND, format_R},   {OPCODE_ANDI, format_I},
    {OPCODE_B, format_B},     {OPCODE_B_COND, format_CB},
    {OPCODE_BL, format_B},    {OPCODE_BR, format_R},
    {OPCODE_CBNZ, format_CB}, {OPCODE_CBZ, format_CB},
    {OPCODE_DUMP, format_R},  {OPCODE_EOR, format_R},
    {OPCODE_EORI, format_I},  {OPCODE_HALT, format_R},
    {OPCODE_LDUR, format_D},  {OPCODE_LDURB, format_D},
    {OPCODE_LDURH, format_D}, {OPCODE_LDURSW, format_D},
    {OPCODE_LSL, format_R},   {OPCODE_LSR, format_R},
    {OPCODE_MUL, format_R},   {OPCODE_ORR, format_R},
    {OPCODE_ORRI, format_I},  {OPCODE_PRNL, format_R},
    {OPCODE_PRNT, format_R},  {OPCODE_SDIV, format_R},
    {OPCODE_SMULH, format_R}, {OPCODE_STUR, format_D},
    {OPCODE_STURB, format_D}, {OPCODE_STURH, format_D},
    {OPCODE_STURW, format_D}, {OPCODE_SUB, format_R},
    {OPCODE_SUBI, format_I},  {OPCODE_SUBIS, format_I},
    {OPCODE_SUBIS, format_I}, {OPCODE_SUBS, format_R},
    {OPCODE_UDIV, format_R},  {OPCODE_UMULH, format_R}};

static const struct {
  const uint32_t opcode;
  void (*func_pointer)(uint64_t*, uint8_t, uint8_t,
                       uint8_t);  // register, Rd, Rm, Rn
} R_format_func_lookup[] = {
    {OPCODE_ADD, ADD}/*,       {OPCODE_AND, format_R},
    {OPCODE_BR, format_R},   {OPCODE_DUMP, format_R},
    {OPCODE_EOR, format_R},  {OPCODE_HALT, format_R},
    {OPCODE_LSL, format_R},  {OPCODE_LSR, format_R},
    {OPCODE_MUL, format_R},  {OPCODE_ORR, format_R},
    {OPCODE_PRNL, format_R}, {OPCODE_PRNT, format_R},
    {OPCODE_SDIV, format_R}, {OPCODE_SMULH, format_R},
    {OPCODE_SUB, format_R},  {OPCODE_SUBS, format_R},
    {OPCODE_UDIV, format_R}, {OPCODE_UMULH, format_R}*/};

/* TODO: Create lookup tables for each of the formats */

static uint32_t get_opcode(uint32_t* word) {
  const int steps[5] = {21, 1, 1, 1, 2};

  unsigned int opcode = *word;

  for (int i = 0; i < 5; i++) {
    opcode = opcode >> steps[i];

    for (int j = 0; j < 37; j++) {
      if (opcode == opcodes[j]) {
        return opcodes[j];
      }
    }
  }

  perror("Unrecognized opcode");
  exit(EXIT_FAILURE);
}

static void parse_R_format(union instruction* i, uint32_t* word) {}

// static void parse_D_format(union instruction* i, uint32_t* word) {}

// static void parse_I_format(union instruction* i, uint32_t* word) {}

// static void parse_B_format(union instruction* i, uint32_t* word) {}

union instruction parse(uint32_t* word) {
  union instruction instr;

  uint32_t opcode = get_opcode(word);
  instruction_format_t type = instruction_format_lookup[opcode].format;

  instr.i.opcode = opcode;

  return instr;
}