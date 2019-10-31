#include "instruction_impl.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

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

void DUMP(uint64_t *X, uint64_t *stack){
    printf("Registers:\n");

    char* reg_name = "     ";
    for(int i = 0; i < 32; i++){
        switch(i){
            case 16: reg_name = "(IP0)";
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
            default: reg_name = "     ";
        }
        printf("%6s X%02d: 0x%016lx (%d)\n", reg_name, i, X[i], (int)X[i]);
    }
}

void EOR(uint64_t *X, uint8_t dest, uint8_t source1, uint8_t source2){
    X[dest] = X[source1] ^ X[source2];
}

void EORI(uint64_t *X, uint8_t dest, uint8_t source, uint64_t immediate){
    X[dest] = X[source] ^ X[immediate];
}

void LDUR(uint64_t *X, uint64_t *stack, uint8_t dest, uint8_t address, uint16_t offset){
    X[dest] = stack[address + (offset / 8)];
}


