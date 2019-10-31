#include "find_opcode.h"
#include "parser.h"
#include <stdint.h>


uint32_t call_opcode(uint32_t instruction) {
  uint32_t opcode = instruction >> 21;
  switch (opcode) {
  case OPCODE_DUMP:
    return OPCODE_DUMP;

  case OPCODE_HALT:
    return OPCODE_HALT;

  case OPCODE_PRNL:
    return OPCODE_PRNL;

  case OPCODE_UMULH:
    return OPCODE_UMULH;

  case OPCODE_UDIV:
    return OPCODE_UDIV;

  case OPCODE_SMULH:
    return OPCODE_SMULH;

  case OPCODE_SDIV:
    return OPCODE_SDIV;

  case OPCODE_MUL:
    return OPCODE_MUL;

  case OPCODE_LDUR:
    return OPCODE_LDUR;

  case OPCODE_STUR:
    return OPCODE_STUR;

  case OPCODE_SUBS:
    return OPCODE_SUSB;

  case OPCODE_BR:
    return OPCODE_BR;

  case OPCODE_LSL:
    return OPCODE_LSL;

  case OPCODE_LSR:
    return OPCODE_LSR;

  case OPCODE_SUB:
    return OPCODE_SUB;

  case OPCODE_EOR:
    return OPCODE_EOR;

  case OPCODE_LDURSW:
    return OPCODE_LDURSW;

  case OPCODE_STURW:
    return OPCODE_STURW;

  case OPCODE_ADDS:
    return OPCODE_ADDS;

  case OPCODE_ORR:
    return OPCODE_ORR;

  case OPCODE_ADD:
    return OPCODE_ADD;

  case OPCODE_AND:
    return OPCODE_AND;

  case OPCODE_LDURH:
    return OPCODE_LDURH;

  case OPCODE_STURH:
    return OPCODE_STURH;

  case OPCODE_LDURB:
    return OPCODE_LDURB;

  case OPCODE_STURB:
    return OPCODE_STURB;

  default:
    opcode = opcode >> 1;
    break;
}
  switch(opcode) {
  case OPCODE_PRNT:
    return OPCODE_PRNT;
    
  case OPCODE_ORRI:
    return OPCODE_ORRI;
    
  case OPCODE_EORI:
    return OPCODE_EORI;
    
  case OPCODE_ADDI:
    return OPCODE_ADDI;
    
  case OPCODE_ANDI:
    return OPCODE_ANDI;
    
  case OPCODE_SUBI:
    return OPCODE_SUBI;
    
  case OPCODE_SUBIS:
    return OPCODE_SUBIS;
    
  default:
    opcode = opcode >> 2;
    break;
  }

  switch(opcode) {
  case OPCODE_CBNZ:
    return OPCODE_CBNZ;
    
  case OPCODE_CBZ:
    return OPCODE_CBZ;
    
  case OPCODE_BC:
    return OPCODE_BC;
    
  default:
    opcode = opcode >> 2;
    break;
  }

  switch(opcode) {
  case OPCODE_B:
    return OPCODE_B;
    
  case OPCODE_BL:
    return OPCODE_BL;
  }
  exit(-1);
}
