#ifndef INSTRUCTION_IMPL_H_
#define INSTRUCTION_IMPL_H_

#include <stdint.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

void ADD(uint64_t *X, uint8_t dest, uint8_t source1, uint8_t source2);

void ADDI(uint64_t *X, uint8_t dest, uint8_t source, uint64_t immediate);

void AND(uint64_t *X, uint8_t dest, uint8_t source1, uint8_t source2);

void ANDI(uint64_t *X, uint8_t dest, uint8_t source, uint64_t immediate);

void B();

uint8_t B_cond(uint64_t *X, uint8_t extention);

void BL();

void BR();

void CBNZ();

void CBZ();

void EOR(uint64_t *X, uint8_t dest, uint8_t source1, uint8_t source2);

void EORI(uint64_t *X, uint8_t dest, uint8_t source, uint64_t immediate);

void HALT();

void LDUR(uint64_t *X, uint64_t *stack, uint8_t dest, uint8_t address, uint16_t offset);

void DUMP(uint64_t *X, size_t main_length, uint64_t *stack, size_t stack_length);

#endif