#ifndef INSTRUCTION_IMPL_H_
#define INSTRUCTION_IMPL_H_

#include <stdint.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

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

/* R instructions */
void ADD(uint64_t *X, uint8_t Rm, uint8_t shamt, uint8_t Rn, uint8_t Rd);

void AND(uint64_t *X, uint8_t Rm, uint8_t shamt, uint8_t Rn, uint8_t Rd);

void EOR(uint64_t *X, uint8_t Rm, uint8_t shamt, uint8_t Rn, uint8_t Rd);

void ORR(uint64_t *X, uint8_t Rm, uint8_t shamt, uint8_t Rn, uint8_t Rd);

void SUB(uint64_t *X, uint8_t Rm, uint8_t shamt, uint8_t Rn, uint8_t Rd);

void UDIV(uint64_t *X, uint8_t Rm, uint8_t shamt, uint8_t Rn, uint8_t Rd);

void UMULH(uint64_t *X, uint8_t Rm, uint8_t shamt, uint8_t Rn, uint8_t Rd);

void BR(uint64_t *X, uint8_t Rm, uint8_t shamt, uint8_t Rn, uint8_t Rd);

void SUBS(uint64_t *X, uint8_t Rm, uint8_t shamt, uint8_t Rn, uint8_t Rd);

/* I instructions */
void ADDI(uint64_t *X, uint8_t Rd, uint8_t Rn, uint64_t ALU_immediate);

void ANDI(uint64_t *X, uint8_t Rd, uint8_t Rn, uint64_t ALU_immediate);

void EORI(uint64_t *X, uint8_t Rd, uint8_t Rn, uint64_t ALU_immediate);

void ORRI(uint64_t *X, uint8_t Rd, uint8_t Rn, uint64_t ALU_immediate);

void SUBI(uint64_t *X, uint8_t Rd, uint8_t Rn, uint64_t ALU_immediate);

void SUBIS(uint64_t *X, uint8_t Rd, uint8_t Rn, uint64_t ALU_immediate);

/* B instructions */
void B(uint64_t *X, uint32_t BR_address);

void BL(uint64_t *X, uint32_t BR_address);

/* CB instructions */
void B_cond(uint64_t *X, uint32_t COND_BR_address, uint8_t Rt);

void CBNZ();

void CBZ();

/* D instructions */
void LDUR(uint64_t *X, uint64_t *stack, uint8_t Rd, uint8_t address, uint16_t offset);


/* custom instructions */
void HALT(uint64_t *X, size_t reg_length, uint64_t *stack, size_t stack_length);

void DUMP(uint64_t *X, size_t reg_length, uint64_t *stack, size_t stack_length);

void PRNL();

void PRNT(uint64_t *X, uint8_t reg);

#endif