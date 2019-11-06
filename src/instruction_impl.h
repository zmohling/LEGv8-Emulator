#ifndef INSTRUCTION_IMPL_H_
#define INSTRUCTION_IMPL_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "parser.h"

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
void ADD(uint64_t *X, instruction_t *);

void ADDD(uint64_t *X, instruction_t *);

void ADDDI(uint64_t *X, instruction_t *);

void AND(uint64_t *X, instruction_t *);

void EOR(uint64_t *X, instruction_t *);

void ORR(uint64_t *X, instruction_t *);

void SUB(uint64_t *X, instruction_t *);

void UDIV(uint64_t *X, instruction_t *);

void UMULH(uint64_t *X, instruction_t *);

void BR(uint64_t *X, instruction_t *);

void SUBS(uint64_t *X, instruction_t *);

/* I instructions */
void ADDI(uint64_t *X, instruction_t *);

void ANDI(uint64_t *X, instruction_t *);

void EORI(uint64_t *X, instruction_t *);

void ORRI(uint64_t *X, instruction_t *);

void SUBI(uint64_t *X, instruction_t *);

void SUBIS(uint64_t *X, instruction_t *);

/* B instructions */
void B(uint64_t *X, instruction_t *);

void BL(uint64_t *X, instruction_t *);

/* CB instructions */
void B_cond(uint64_t *X, uint32_t COND_BR_address, uint8_t Rt);

void CBNZ();

void CBZ();

/* D instructions */
void LDUR(uint64_t *X, uint8_t *stack, instruction_t *);

//STUR()???

/* custom instructions */
void HALT(uint64_t *X, size_t reg_length, uint64_t *stack, size_t stack_length);

void DUMP(uint64_t *X, size_t reg_length, uint64_t *stack, size_t stack_length);

void PRNL();

void PRNT(uint64_t *X, uint8_t reg);

#endif