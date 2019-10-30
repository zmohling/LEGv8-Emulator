#ifndef INSTRUCTION_IMPL_H_
#define INSTRUCTION_IMPL_H_

#include <stdint.h>

void ADD(uint64_t *X, uint8_t dest, uint8_t source1, uint8_t source2);

void ADDI(uint64_t *X, uint8_t dest, uint8_t source, uint64_t immediate);

void AND(uint64_t *X, uint8_t dest, uint8_t source1, uint8_t source2);

void ANDI(uint64_t *X, uint8_t dest, uint8_t source, uint64_t immediate);



#endif