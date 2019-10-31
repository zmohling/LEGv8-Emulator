#include "find_opcode.h"
#include "instruction_impl.h"
#include "parser.h"
#include <stdint.h>


void call_opcode(uint32_t instruction) {
  uint32_t opcode = instruction >> 21;
  switch (opcode) {
  case OPCODE_DUMP:
    DUMP();
    return;

  case OPCODE_HALT:
    HALT();
    return;

  case OPCODE_PRNL:
    PRNL();
    return;

  case OPCODE_UMULH:
    UMULH();
    return;

  case OPCODE_UDIV:
    UDIV();
    return;

  case OPCODE_SMULH:
    SMULH();
    return;

  case OPCODE_SDIV:
    SDIV();
    return;

  case OPCODE_MUL:
    MUL();
    return;

  case OPCODE_LDUR:
    LDUR();
    return;

  case OPCODE_STUR:
    STUR();
    return;

  case OPCODE_SUBS:
    SUBS();
    return;

  case OPCODE_BR:
    BR();
    return;

  case OPCODE_LSL:
    LSL();
    return;

  case OPCODE_LSR:
    LSR();
    return;

  case OPCODE_SUB:
    SUB();
    return;

  case OPCODE_EOR:
    EOR();
    return;

  case OPCODE_LDURSW:
    LDURSW();
    return;

  case OPCODE_STURW:
    STURW();
    return;

  case OPCODE_ADDS:
    ADDS();
    return;

  case OPCODE_ORR:
    ORR();
    return;

  case OPCODE_ADD:
    ADD();
    return;

  case OPCODE_AND:
    AND();
    return;

  case OPCODE_LDURH:
    LDURH();
    return;

  case OPCODE_STURH:
    STURH();
    return;

  case OPCODE_LDURB:
    LDURB();
    return;

  case OPCODE_STURB:
    STURB();
    return;

  default:
    opcode = opcode >> 1;
    break;
}
  switch(opcode) {
  case OPCODE_PRNT:
    PRNT();
    return;
    
  case OPCODE_ORRI:
    ORRI();
    return;
    
  case OPCODE_EORI:
    EORI();
    return;
    
  case OPCODE_ADDI:
    ADDI();
    return;
    
  case OPCODE_ANDI:
    ANDI();
    return;
    
  case OPCODE_SUBI:
    SUBI();
    return;
    
  case OPCODE_SUBIS:
    SUBIS();
    return;
    
  default:
    opcode = opcode >> 2;
    break;
  }

  switch(opcode) {
  case OPCODE_CBNZ:
    CBNZ();
    return;
    
  case OPCODE_CBZ:
    CBZ();
    return;
    
  case OPCODE_BC:
    BC();
    return;
    
  default:
    opcode = opcode >> 2;
    break;
  }

  switch(opcode) {
  case OPCODE_B:
    B();
    return;
    
  case OPCODE_BL:
    BL();
    return;
  }
  return; // should be exception here for if the opcode wasn't found or something similar
}
