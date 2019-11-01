#include "instruction_impl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

/* ---------- R instructions ---------- */

void ADD(uint64_t *X, uint8_t Rm, uint8_t shamt, uint8_t Rn, uint8_t Rd){
  X[Rd] = X[Rn] + X[Rm];
}

void AND(uint64_t *X, uint8_t Rm, uint8_t shamt, uint8_t Rn, uint8_t Rd){
  X[Rd] = X[Rn] & X[Rm];
}

void EOR(uint64_t *X, uint8_t Rm, uint8_t shamt, uint8_t Rn, uint8_t Rd){
  X[Rd] = X[Rn] ^ X[Rm];
}

void ORR(uint64_t *X, uint8_t Rm, uint8_t shamt, uint8_t Rn, uint8_t Rd){
  X[Rd] = X[Rn] | X[Rm];
}

void SUB(uint64_t *X, uint8_t Rm, uint8_t shamt, uint8_t Rn, uint8_t Rd){
  X[Rd] = X[Rn] - X[Rm];
}

void UDIV(uint64_t *X, uint8_t Rm, uint8_t shamt, uint8_t Rn, uint8_t Rd){
  X[Rd] = X[Rn] / X[Rm];
}

void UMULH(uint64_t *X, uint8_t Rm, uint8_t shamt, uint8_t Rn, uint8_t Rd){
  X[Rd] = X[Rn] * X[Rm];
}

void BR(uint64_t *X, uint8_t Rm, uint8_t shamt, uint8_t Rn, uint8_t Rd){
  X[PC] = X[Rd];
}

/* ---------- I instructions ---------- */

void ADDI(uint64_t *X, uint8_t Rd, uint8_t Rn, uint64_t ALU_immediate){
  X[Rd] = X[Rn] + ALU_immediate;
}

void ANDI(uint64_t *X, uint8_t Rd, uint8_t Rn, uint64_t ALU_immediate){
  X[Rd] = X[Rn] & ALU_immediate;
}

void EORI(uint64_t *X, uint8_t Rd, uint8_t Rn, uint64_t ALU_immediate){
  X[Rd] = X[Rn] ^ X[ALU_immediate];
}

void ORRI(uint64_t *X, uint8_t Rd, uint8_t Rn, uint64_t ALU_immediate){
  X[Rd] = X[Rn] | ALU_immediate;
}

void SUBI(uint64_t *X, uint8_t Rd, uint8_t Rn, uint64_t ALU_immediate){
  X[Rd] = X[Rn] - ALU_immediate;
}

/* ---------- B instructions ---------- */

void B(uint64_t *X, uint32_t BR_address){
  X[PC] = X[PC] + (BR_address * 4);
}

void BL(uint64_t *X, uint32_t BR_address){
  X[LR] = X[PC] + (1 * 4);
  X[PC] = X[PC] + (BR_address * 4);
}

/* ---------- CB instructions --------- */

/* ---------- D instructions ---------- */

void LDUR(uint64_t *X, uint64_t *stack, uint8_t Rd, uint8_t address, uint16_t offset){
  X[Rd] = stack[address + (offset / 8)];
}

/* -------- Custom instructions ------- */

char printable_char(uint8_t c){
  return isprint(c) ? c : '.';
}

void print_hexdump(int8_t *start, size_t size){
  size_t i;
  for (i = 0; i < size - (size % 16); i += 16) {
    printf( "%08x "
        " %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx "
        " %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx "
        " |%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c|\n",
        (int32_t) i,
        start[i +  0], start[i +  1], start[i +  2], start[i +  3],
        start[i +  4], start[i +  5], start[i +  6], start[i +  7],
        start[i +  8], start[i +  9], start[i + 10], start[i + 11],
        start[i + 12], start[i + 13], start[i + 14], start[i + 15],
        printable_char(start[i +  0]), printable_char(start[i +  1]),
        printable_char(start[i +  2]), printable_char(start[i +  3]),
        printable_char(start[i +  4]), printable_char(start[i +  5]),
        printable_char(start[i +  6]), printable_char(start[i +  7]),
        printable_char(start[i +  8]), printable_char(start[i +  9]),
        printable_char(start[i + 10]), printable_char(start[i + 11]),
        printable_char(start[i + 12]), printable_char(start[i + 13]),
        printable_char(start[i + 14]), printable_char(start[i + 15]));
  }
  printf("%08x\n", (int32_t) size);
}

void hexdump(FILE *f, int8_t *start, size_t size){
  size_t i;
  for (i = 0; i < size - (size % 16); i += 16) {
    fprintf(f,
        "%08x "
        " %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx "
        " %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx "
        " |%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c|\n",
        (int32_t) i,
        start[i +  0], start[i +  1], start[i +  2], start[i +  3],
        start[i +  4], start[i +  5], start[i +  6], start[i +  7],
        start[i +  8], start[i +  9], start[i + 10], start[i + 11],
        start[i + 12], start[i + 13], start[i + 14], start[i + 15],
        printable_char(start[i +  0]), printable_char(start[i +  1]),
        printable_char(start[i +  2]), printable_char(start[i +  3]),
        printable_char(start[i +  4]), printable_char(start[i +  5]),
        printable_char(start[i +  6]), printable_char(start[i +  7]),
        printable_char(start[i +  8]), printable_char(start[i +  9]),
        printable_char(start[i + 10]), printable_char(start[i + 11]),
        printable_char(start[i + 12]), printable_char(start[i + 13]),
        printable_char(start[i + 14]), printable_char(start[i + 15]));
  }
  fprintf(f, "%08x\n", (int32_t) size);
}

void DUMP(uint64_t *X, size_t main_length, uint64_t *stack, size_t stack_length){
  printf("\nRegisters:\n");

  char* reg_name = "   ";
  for(int i = 0; i < 32; i++){
    switch(i){
      case 16: reg_name = "(PC)";
        break;
      case 17: reg_name = "(IP1)";
        break;
      case 28: reg_name = "(SP)";
        break;
      case 29: reg_name = "(FP)";
        break;
      case 30: reg_name = "(LR)";
        break;
      case 31: reg_name = "(XZR)";
        break;
      default: reg_name = "   ";
    }
    printf("%6s X%02d: 0x%016lx (%d)\n", reg_name, i, X[i], (int)X[i]);
  }

  printf("\nStack:\n");
  print_hexdump((int8_t *)stack, stack_length);

  printf("\nMain Memory:\n");
  print_hexdump((int8_t *)X, main_length);
}

void HALT(uint64_t *X, size_t main_length, uint64_t *stack, size_t stack_length){
  DUMP(X, main_length, stack, stack_length);
  exit(-1);
}

void PRNL(){
  printf("\n");
}

void PRNT(uint64_t *X, uint8_t reg){
  printf("X%02d: 0x%016lx (%d)\n", reg, X[reg], (int)X[reg]);
}