#include "instruction_impl.h"
#include <stdint.h>

void ADD(uint64_t *X, uint8_t dest, uint8_t source1, uint8_t source2){
    X[dest] = X[source1] + X[source2];
}

void ADDI(uint64_t *X, uint8_t dest, uint8_t source, uint64_t immediate){
    X[dest] = X[source] + immediate;
}

void AND(uint64_t *X, uint8_t dest, uint8_t source1, uint8_t source2){
    X[dest] = X[source1] & X[source2];
}

void ANDI(uint64_t *X, uint8_t dest, uint8_t source, uint64_t immediate){
    X[dest] = X[source] & immediate;
}

// missing methods here

void EOR(uint64_t *X, uint8_t dest, uint8_t source1, uint8_t source2){
    X[dest] = X[source1] ^ X[source2];
}

void EORI(uint64_t *X, uint8_t dest, uint8_t source, uint64_t immediate){
    X[dest] = X[source] ^ X[immediate];
}

void LDUR(uint64_t *X, uint64_t *stack, uint8_t dest, uint8_t address, uint16_t offset){
       
}


