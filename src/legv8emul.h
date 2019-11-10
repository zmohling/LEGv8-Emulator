#ifndef LEGV8EMUL_H_
#define LEGV8EMUL_H_

#include <stdint.h>

#define MAIN_MEMORY_SIZE    4096
#define STACK_SIZE          512
#define REG_SIZE            32

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

typedef struct machine_state {
  uint64_t X[REG_SIZE];                 // registers
  uint8_t stack[STACK_SIZE];            // stack
  uint8_t main_mem[MAIN_MEMORY_SIZE];   // main memory
  uint32_t* instructions;               // all instructions
  uint8_t FLAGS[FLAGS_LENGTH];
} machine_state_t;

#endif