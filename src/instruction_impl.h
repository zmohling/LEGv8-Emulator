#ifndef INSTRUCTION_IMPL_H_
#define INSTRUCTION_IMPL_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "legv8emul.h"

// clang-format off
#define PC    16
#define IP1   17
#define SP    28
#define FP    29
#define LR    30
#define XZR   31

#define EQ    0
#define NE    1
#define HS    2
#define LO    3
#define MI    4
#define PL    5
#define VS    6
#define VC    7
#define HI    8
#define LS    9
#define GE    10
#define LT    11
#define GT    12
#define LE    13
#define FLAGS_LENGTH 14
// clang-format on

/* R instructions */
void ADD(machine_state_t *machine_state, instruction_t *instr);

void AND(machine_state_t *machine_state, instruction_t *instr);

void EOR(machine_state_t *machine_state, instruction_t *instr);

void ORR(machine_state_t *machine_state, instruction_t *instr);

void SUB(machine_state_t *machine_state, instruction_t *instr);

void UDIV(machine_state_t *machine_state, instruction_t *instr);

void BR(machine_state_t *machine_state, instruction_t *instr);

void SUBS(machine_state_t *machine_state, instruction_t *instr);

void LSL(machine_state_t *machine_state, instruction_t *instr);

void LSR(machine_state_t *machine_state, instruction_t *instr);

void MUL(machine_state_t *machine_state, instruction_t *instr);

/* I instructions */
void ADDI(machine_state_t *machine_state, instruction_t *instr);

void ANDI(machine_state_t *machine_state, instruction_t *instr);

void EORI(machine_state_t *machine_state, instruction_t *instr);

void ORRI(machine_state_t *machine_state, instruction_t *instr);

void SUBI(machine_state_t *machine_state, instruction_t *instr);

void SUBIS(machine_state_t *machine_state, instruction_t *instr);

/* B instructions */
void B(machine_state_t *machine_state, instruction_t *instr);

void BL(machine_state_t *machine_state, instruction_t *instr);

/* CB instructions */
void B_COND(machine_state_t *machine_state, instruction_t *instr);

void CBNZ(machine_state_t *machine_state, instruction_t *instr);

void CBZ(machine_state_t *machine_state, instruction_t *instr);

/* D instructions */
void LDUR(machine_state_t *machine_state, instruction_t *instr);

void STUR(machine_state_t *machine_state, instruction_t *instr);

/* custom instructions */
void HALT(machine_state_t *machine_state, instruction_t *instr);

void DUMP(machine_state_t *machine_state, instruction_t *instr);

void PRNL(machine_state_t *machine_state, instruction_t *instr);

void PRNT(machine_state_t *machine_state, instruction_t *instr);

#endif