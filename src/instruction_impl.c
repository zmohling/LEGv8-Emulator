#include "instruction_impl.h"

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint8_t FLAGS[FLAGS_LENGTH];

void set_all_flags(int s) {
  for (int i = 0; i < FLAGS_LENGTH; i++) {
    FLAGS[i] = 0;
  }

  if (s == 0) {
    FLAGS[EQ] = 1;
  }
  if (s >= 0) {
    FLAGS[GE] = 1;
    FLAGS[HS] = 1;
    FLAGS[PL] = 1;
  }
  if (s > 0) {
    FLAGS[GT] = 1;
    FLAGS[HI] = 1;
  }
  if (s <= 0) {
    FLAGS[LE] = 1;
    FLAGS[LS] = 1;
  }
  if (s < 0) {
    FLAGS[LO] = 1;
    FLAGS[LT] = 1;
    FLAGS[MI] = 1;
  }
  if (s != 0) {
    FLAGS[NE] = 1;
  }
}

/* ---------- R instructions ---------- */

void ADDD(uint64_t *X, instruction_t *instr) {
  printf("ADD Rm: %u, shamt: %u, Rn: %u, Rd: %u\n", instr->R.Rm, instr->R.shamt,
         instr->R.Rn, instr->R.Rd);
}

void ADDDI(uint64_t *X, instruction_t *instr) {
  printf("ADDI ALU_immediate: %u, Rn: %u, Rd: %u\n", instr->I.ALU_immediate,
         instr->I.Rn, instr->I.Rd);
}

void ADD(uint64_t *X, instruction_t *instr) {
  X[instr->R.Rd] = X[instr->R.Rn] + X[instr->R.Rm];
}

void AND(uint64_t *X, instruction_t *instr) {
  X[instr->R.Rd] = X[instr->R.Rn] & X[instr->R.Rm];
}

void EOR(uint64_t *X, instruction_t *instr) {
  X[instr->R.Rd] = X[instr->R.Rn] ^ X[instr->R.Rm];
}

void ORR(uint64_t *X, instruction_t *instr) {
  X[instr->R.Rd] = X[instr->R.Rn] | X[instr->R.Rm];
}

void SUB(uint64_t *X, instruction_t *instr) {
  X[instr->R.Rd] = X[instr->R.Rn] - X[instr->R.Rm];
}

void UDIV(uint64_t *X, instruction_t *instr) {
  X[instr->R.Rd] = X[instr->R.Rn] / X[instr->R.Rm];
}

void UMULH(uint64_t *X, instruction_t *instr) {
  X[instr->R.Rd] = X[instr->R.Rn] * X[instr->R.Rm];
}

void BR(uint64_t *X, instruction_t *instr) {
  X[PC] = X[instr->R.Rd];
}

void SUBS(uint64_t *X, instruction_t *instr) {
  int s = (int)X[instr->R.Rn] - (int)X[instr->R.Rm];

  set_all_flags(s);
}

/* ---------- I instructions ---------- */

void ADDI(uint64_t *X, instruction_t *instr) {
  X[instr->I.Rd] = X[instr->I.Rn] + instr->I.ALU_immediate;
}

void ANDI(uint64_t *X, instruction_t *instr) {
  X[instr->I.Rd] = X[instr->I.Rn] & instr->I.ALU_immediate;
}

void EORI(uint64_t *X, instruction_t *instr) {
  X[instr->I.Rd] = X[instr->I.Rn] ^ instr->I.ALU_immediate;
}

void ORRI(uint64_t *X, instruction_t *instr) {
  X[instr->I.Rd] = X[instr->I.Rn] | instr->I.ALU_immediate;
}

void SUBI(uint64_t *X, instruction_t *instr) {
  X[instr->I.Rd] = X[instr->I.Rn] - instr->I.ALU_immediate;
}

void SUBIS(uint64_t *X, instruction_t *instr) {
  int s = (int)X[instr->I.Rn] - (int)instr->I.ALU_immediate;

  set_all_flags(s);
}

/* ---------- B instructions ---------- */

void B(uint64_t *X, instruction_t *instr) { 
  X[PC] = X[PC] + (instr->B.BR_address * 4); 
}

void BL(uint64_t *X, instruction_t *instr) {
  X[LR] = X[PC] + (1 * 4);
  X[PC] = X[PC] + (instr->B.BR_address * 4);
}

/* ---------- CB instructions --------- */

void B_cond(uint64_t *X, uint32_t COND_BR_address, uint8_t Rt) {
  //TODO
}

/* ---------- D instructions ---------- */



/* -------- Custom instructions ------- */
//didn't change any of these to be based on instruction type

char printable_char(uint8_t c) { return isprint(c) ? c : '.'; }

void print_hexdump(int8_t *start, size_t size) {
  size_t i;
  for (i = 0; i < size - (size % 16); i += 16) {
    printf(
        "%08x "
        " %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx "
        " %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx "
        " |%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c|\n",
        (int32_t)i, start[i + 0], start[i + 1], start[i + 2], start[i + 3],
        start[i + 4], start[i + 5], start[i + 6], start[i + 7], start[i + 8],
        start[i + 9], start[i + 10], start[i + 11], start[i + 12],
        start[i + 13], start[i + 14], start[i + 15],
        printable_char(start[i + 0]), printable_char(start[i + 1]),
        printable_char(start[i + 2]), printable_char(start[i + 3]),
        printable_char(start[i + 4]), printable_char(start[i + 5]),
        printable_char(start[i + 6]), printable_char(start[i + 7]),
        printable_char(start[i + 8]), printable_char(start[i + 9]),
        printable_char(start[i + 10]), printable_char(start[i + 11]),
        printable_char(start[i + 12]), printable_char(start[i + 13]),
        printable_char(start[i + 14]), printable_char(start[i + 15]));
  }
  printf("%08x\n", (int32_t)size);
}

void hexdump(FILE *f, int8_t *start, size_t size) {
  size_t i;
  for (i = 0; i < size - (size % 16); i += 16) {
    fprintf(f,
            "%08x "
            " %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx "
            " %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx "
            " |%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c|\n",
            (int32_t)i, start[i + 0], start[i + 1], start[i + 2], start[i + 3],
            start[i + 4], start[i + 5], start[i + 6], start[i + 7],
            start[i + 8], start[i + 9], start[i + 10], start[i + 11],
            start[i + 12], start[i + 13], start[i + 14], start[i + 15],
            printable_char(start[i + 0]), printable_char(start[i + 1]),
            printable_char(start[i + 2]), printable_char(start[i + 3]),
            printable_char(start[i + 4]), printable_char(start[i + 5]),
            printable_char(start[i + 6]), printable_char(start[i + 7]),
            printable_char(start[i + 8]), printable_char(start[i + 9]),
            printable_char(start[i + 10]), printable_char(start[i + 11]),
            printable_char(start[i + 12]), printable_char(start[i + 13]),
            printable_char(start[i + 14]), printable_char(start[i + 15]));
  }
  fprintf(f, "%08x\n", (int32_t)size);
}

void DUMP(uint64_t *X, size_t main_length, uint64_t *stack,
          size_t stack_length) {
  printf("\nRegisters:\n");

  char *reg_name = "   ";
  for (int i = 0; i < 32; i++) {
    switch (i) {
      case 16:
        reg_name = "(PC)";
        break;
      case 17:
        reg_name = "(IP1)";
        break;
      case 28:
        reg_name = "(SP)";
        break;
      case 29:
        reg_name = "(FP)";
        break;
      case 30:
        reg_name = "(LR)";
        break;
      case 31:
        reg_name = "(XZR)";
        break;
      default:
        reg_name = "   ";
    }
    printf("%6s X%02d: 0x%016lx (%d)\n", reg_name, i, X[i], (int)X[i]);
  }

  printf("\nStack:\n");
  print_hexdump((int8_t *)stack, stack_length);

  printf("\nMain Memory:\n");
  print_hexdump((int8_t *)X, main_length);
}

void HALT(uint64_t *X, size_t main_length, uint64_t *stack,
          size_t stack_length) {
  DUMP(X, main_length, stack, stack_length);
  exit(-1);
}

void PRNL() { printf("\n"); }

void PRNT(uint64_t *X, uint8_t reg) {
  printf("X%02d: 0x%016lx (%d)\n", reg, X[reg], (int)X[reg]);
}
