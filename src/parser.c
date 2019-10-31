#include "parser.h"

#include <stdint.h>

static const struct {
  const uint16_t opcode;
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
    {OPCODE_UDIV, format_R},  {OPCODE_UMULH, format_R},
};

static uint16_t get_opcode(uint32_t* word) {}

union instruction parse(uint32_t* word) {
  union instruction i;
}
