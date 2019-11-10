#include "instruction_impl.h"
#include "legv8emul.h"

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void set_all_flags(machine_state_t *machine_state, int s) {
  for (int i = 0; i < FLAGS_LENGTH; i++) {
    machine_state->FLAGS[i] = 0;
  }

  if (s == 0) {
    machine_state->FLAGS[EQ] = 1;
  }
  if (s >= 0) {
    machine_state->FLAGS[GE] = 1;
    machine_state->FLAGS[HS] = 1;
    machine_state->FLAGS[PL] = 1;
  }
  if (s > 0) {
    machine_state->FLAGS[GT] = 1;
    machine_state->FLAGS[HI] = 1;
  }
  if (s <= 0) {
    machine_state->FLAGS[LE] = 1;
    machine_state->FLAGS[LS] = 1;
  }
  if (s < 0) {
    machine_state->FLAGS[LO] = 1;
    machine_state->FLAGS[LT] = 1;
    machine_state->FLAGS[MI] = 1;
  }
  if (s != 0) {
    machine_state->FLAGS[NE] = 1;
  }
}

/* ---------- R instructions ---------- */

void ADD(machine_state_t *machine_state, instruction_t *instr) {
  machine_state->X[instr->R.Rd] = machine_state->X[instr->R.Rn] + 
                                    machine_state->X[instr->R.Rm];
}

void AND(machine_state_t *machine_state, instruction_t *instr) {
  machine_state->X[instr->R.Rd] = machine_state->X[instr->R.Rn] & 
                                    machine_state->X[instr->R.Rm];
}

void EOR(machine_state_t *machine_state, instruction_t *instr) {
  machine_state->X[instr->R.Rd] = machine_state->X[instr->R.Rn] ^ 
                                    machine_state->X[instr->R.Rm];
}

void ORR(machine_state_t *machine_state, instruction_t *instr) {
  machine_state->X[instr->R.Rd] = machine_state->X[instr->R.Rn] | 
                                    machine_state->X[instr->R.Rm];
}

void SUB(machine_state_t *machine_state, instruction_t *instr) {
  machine_state->X[instr->R.Rd] = machine_state->X[instr->R.Rn] - 
                                    machine_state->X[instr->R.Rm];
}

void UDIV(machine_state_t *machine_state, instruction_t *instr) {
  machine_state->X[instr->R.Rd] = machine_state->X[instr->R.Rn] / 
                                    machine_state->X[instr->R.Rm];
}

void BR(machine_state_t *machine_state, instruction_t *instr) {
  machine_state->X[PC] = machine_state->X[instr->R.Rd];
}

void SUBS(machine_state_t *machine_state, instruction_t *instr) {
  int s = (int)machine_state->X[instr->R.Rn] - (int)machine_state->X[instr->R.Rm];
  if(instr->R.Rd != XZR){
    machine_state->X[instr->R.Rd] = (uint64_t) s;
  }
  set_all_flags(machine_state, s);
}

void LSL(machine_state_t *machine_state, instruction_t *instr){
  machine_state->X[instr->R.Rd] = machine_state->X[instr->R.Rn ] << instr->R.shamt;
}

void LSR(machine_state_t *machine_state, instruction_t *instr){
  machine_state->X[instr->R.Rd] = machine_state->X[instr->R.Rn ] >> instr->R.shamt;
}

void MUL(machine_state_t *machine_state, instruction_t *instr){
  machine_state->X[instr->R.Rd] = machine_state->X[instr->R.Rn ] * 
                                    machine_state->X[instr->R.Rm];
}

/* ---------- I instructions ---------- */

void ADDI(machine_state_t *machine_state, instruction_t *instr) {
  machine_state->X[instr->I.Rd] = machine_state->X[instr->I.Rn] + 
                                    instr->I.ALU_immediate;
}

void ANDI(machine_state_t *machine_state, instruction_t *instr) {
  machine_state->X[instr->I.Rd] = machine_state->X[instr->I.Rn] & 
                                    instr->I.ALU_immediate;
}

void EORI(machine_state_t *machine_state, instruction_t *instr) {
  machine_state->X[instr->I.Rd] = machine_state->X[instr->I.Rn] ^ 
                                    instr->I.ALU_immediate;
}

void ORRI(machine_state_t *machine_state, instruction_t *instr) {
  machine_state->X[instr->I.Rd] = machine_state->X[instr->I.Rn] | 
                                    instr->I.ALU_immediate;
}

void SUBI(machine_state_t *machine_state, instruction_t *instr) {
  machine_state->X[instr->I.Rd] = machine_state->X[instr->I.Rn] - 
                                    instr->I.ALU_immediate;
}

void SUBIS(machine_state_t *machine_state, instruction_t *instr) {
  int s = (int)machine_state->X[instr->I.Rn] - (int)instr->I.ALU_immediate;
  if(instr->I.Rd != XZR){
    machine_state->X[instr->I.Rd] = (uint64_t) s;
  }
  set_all_flags(machine_state, s);
}

/* ---------- B instructions ---------- */

void B(machine_state_t *machine_state, instruction_t *instr) { 
  machine_state->X[PC] = machine_state->X[PC] + (instr->B.BR_address * 4); 
}

void BL(machine_state_t *machine_state, instruction_t *instr) {
  machine_state->X[LR] = machine_state->X[PC] + (1 * 4);
  machine_state->X[PC] = machine_state->X[PC] + (instr->B.BR_address * 4);
}

/* ---------- CB instructions --------- */

void B_COND(machine_state_t *machine_state, instruction_t *instr) {
  if(machine_state->FLAGS[instr->CB.Rt]){
    machine_state->X[PC] = machine_state->X[PC] + (instr->CB.COND_BR_address * 4); 
  }
}

void CBNZ(machine_state_t *machine_state, instruction_t *instr){
  if(machine_state->X[instr->CB.Rt] != 0){
    machine_state->X[PC] = machine_state->X[PC] + (instr->CB.COND_BR_address * 4);
  }
}

void CBZ(machine_state_t *machine_state, instruction_t *instr){
  if(machine_state->X[instr->CB.Rt] == 0){
    machine_state->X[PC] = machine_state->X[PC] + (instr->CB.COND_BR_address * 4);
  }
}

/* ---------- D instructions ---------- */

void LDUR(machine_state_t *machine_state, instruction_t *instr){
  uint64_t build_num = 0;
  for(int i = 0; i < 8; i ++){
    build_num = build_num << 8;
    if(instr->D.Rn == SP || instr->D.Rn == FP){
      build_num = build_num | machine_state->stack[machine_state->X[instr->D.Rn] + 
                                    instr->D.DT_address + i];
    }else{
      build_num = build_num | machine_state->main_mem[machine_state->X[instr->D.Rn] + 
                                    instr->D.DT_address + i];
    }
  }
  machine_state->X[instr->D.Rt] = build_num;
}

void STUR(machine_state_t *machine_state, instruction_t *instr){
  int shift = 0;
  for(int i = 7; i >= 0; i--){
    if(instr->D.Rn == SP || instr->D.Rn == FP){
      machine_state->stack[machine_state->X[instr->D.Rn] + instr->D.DT_address + i] = 
                            (uint8_t) (machine_state->X[instr->D.Rt] >> (shift * 8) & 0xff);
    }else{
      machine_state->main_mem[machine_state->X[instr->D.Rn] + instr->D.DT_address + i] = 
                            (uint8_t) (machine_state->X[instr->D.Rt] >> (shift * 8) & 0xff);
    }
    shift++;
  }
}

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

void DUMP(machine_state_t *machine_state, instruction_t *instr) {
  printf("\nRegisters:\n");

  char *reg_name = "   ";
  for (int i = 0; i < REG_SIZE; i++) {
    switch (i) {
      case PC:
        reg_name = "(PC)";
        break;
      case IP1:
        reg_name = "(IP1)";
        break;
      case SP:
        reg_name = "(SP)";
        break;
      case FP:
        reg_name = "(FP)";
        break;
      case LR:
        reg_name = "(LR)";
        break;
      case XZR:
        reg_name = "(XZR)";
        break;
      default:
        reg_name = "   ";
    }
    printf("%6s X%02d: 0x%016lx (%d)\n", reg_name, i, machine_state->X[i], 
          (int)machine_state->X[i]);
  }

  printf("\nStack:\n");
  print_hexdump((int8_t *)machine_state->stack, STACK_SIZE);

  printf("\nMain Memory:\n");
  print_hexdump((int8_t *)machine_state->main_mem, MAIN_MEMORY_SIZE);
}

void HALT(machine_state_t *machine_state, instruction_t *instr) {
  DUMP(machine_state, instr);
  exit(-1);
}

void PRNL(machine_state_t *machine_state, instruction_t *instr) { printf("\n"); }

void PRNT(machine_state_t *machine_state, instruction_t *instr) {
  printf("X%02d: 0x%016lx (%d)\n", instr->R.Rd, machine_state->X[instr->R.Rd], 
          (int)machine_state->X[instr->R.Rd]);
}