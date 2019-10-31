#include "find_opcode.h"
#include "instruction_impl.h"
#include <stdint.h>


void call_opcode(uint32_t instruction) {
  int found = 0;
  uint32_t opcode = instruction >> 21;
  switch (opcode) {
  case 11111111110:
    found = 1;
    DUMP();
    break;

  case 11111111111:
    found = 1;
    HALT();
    break;

  case 11111111100:
    found = 1;
    PRNL();
    break;

  case 10011011110:
    found = 1;
    UMULH();
    break;

  case 10011010110:
    found = 1;
    UDIV();
    break;

  case 10011011010:
    found = 1;
    SMULH();
    break;

  case 10011010110:
    found = 1;
    SDIV();
    break;

  case 10011011000:
    found = 1;
    MUL();
    break;

  case 11111000010:
    found = 1;
    LDUR();
    break;

  case 11111000000:
    found = 1;
    STUR();
    break;

  case 11101011000:
    found = 1;
    SUBS();
    break;

  case 11010110000:
    found = 1;
    BR();
    break;

  case 11010011011:
    found = 1;
    LSL();
    break;

  case 11010011010:
    found = 1;
    LSR();
    break;

  case 11001011000:
    found = 1;
    SUB();
    break;

  case 11101010000:
    found = 1;
    EOR();
    break;

  case 10111000100:
    found = 1;
    LDURSW();
    break;

  case 10111000000:
    found = 1;
    STURW();
    break;

  case 10101011000:
    found = 1;
    ADDS();
    break;

  case 10101010000:
    found = 1;
    ORR();
    break;

  case 10001011000:
    found = 1;
    ADD();
    break;

  case 10001010000:
    found = 1;
    AND();
    break;

  case 01111000010:
    found = 1;
    LDURH();
    break;

  case 01111000000:
    found = 1;
    STURH();
    break;

  case 00111000010:
    found = 1;
    LDURB();
    break;

  case 00111000000:
    found = 1;
    STURB();
    break;

  default:
    opcode = opcode >> 1;
    break;
}
  if (!found) {
    switch(opcode) {
    case 1111111101:
      found = 1;
      PRNT();
      break;

    case 1011001000:
      found = 1;
      ORRI();
      break;

    case 1101001000:
      found = 1;
      EORI();
      break;

    case 1001000100:
      found = 1;
      ADDI();
      break;

    case 1001001000:
      found = 1;
      ANDI();
      break;

    case 1101000100:
      found = 1;
      SUBI();
      break;

    case 1111000100:
      found = 1;
      SUBIS();
      break;

    default:
      opcode = opcode >> 2;
      break;
    }
  }

  if (!found) {
    switch(opcode) {
    case 10110100:
      found = 1;
      CBNZ();
      break;

    case 10110101:
      found = 1;
      CBZ();
      break;

    case 01010100:
      found = 1;
      BC();
      break;

    default:
      opcode = opcode >> 2;
      break;
    }
  }

  if (!found) {
    switch(opcode) {
    case 000101:
      found = 1;
      B();
      break;

    case 100101:
      found = 1;
      BL();
      break;
    }
  }
}
