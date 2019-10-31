#include <stdio.h>
#include <stdint.h>
#include "instruction_impl.h"
#include "reader.h"


uint64_t X[512];            // main memory
uint64_t stack[64];         // stack
uint32_t* instructions;     // all instructions

/*
Print out the usage for this program
*/
void usage(){
    printf("./legv8emul <assembled legv8asm .machine file>");
}



int main(int argc, char* argv[]){
    
    if(argc == 1){
        // create uint32_t array of instructions
    }else{
        usage();
    }


    ADDI(X, 8, 8, -2);
    ADDI(X, 9, 9, 1);
    ADD(X, 9, 9, 8);

    printf("%d\n", (int)X[9]);

    return 0;
}