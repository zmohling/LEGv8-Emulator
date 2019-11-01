#ifndef INSTRUCTION_IMPL_H_
#define INSTRUCTION_IMPL_H_

#include <stdint.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

/* R instructions */
void ADD(uint64_t *X, uint8_t Rm, uint8_t shamt, uint8_t Rn, uint8_t Rd);

void AND(uint64_t *X, uint8_t Rm, uint8_t shamt, uint8_t Rn, uint8_t Rd);

void EOR(uint64_t *X, uint8_t Rm, uint8_t shamt, uint8_t Rn, uint8_t Rd);

void SUB(uint64_t *X, uint8_t Rm, uint8_t shamt, uint8_t Rn, uint8_t Rd);

void UDIV(uint64_t *X, uint8_t Rm, uint8_t shamt, uint8_t Rn, uint8_t Rd);

void UMULH(uint64_t *X, uint8_t Rm, uint8_t shamt, uint8_t Rn, uint8_t Rd);

void BR();

/* I instructions */
void ADDI(uint64_t *X, uint8_t Rd, uint8_t Rn, uint64_t ALU_immediate);

void ANDI(uint64_t *X, uint8_t Rd, uint8_t Rn, uint64_t ALU_immediate);

void EORI(uint64_t *X, uint8_t Rd, uint8_t Rn, uint64_t ALU_immediate);

void SUBI(uint64_t *X, uint8_t Rd, uint8_t Rn, uint64_t ALU_immediate);

/* B instructions */
void B();

void BL();

/* CB instructions */
uint8_t B_cond(uint64_t *X, uint8_t extention);

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