#ifndef PARSER_H_
#define PARSER_H_

#include <stdint.h>
#include <stdlib.h>

// clang-format off
#define OPCODE_ADD    0b10001011000000000000000000000000
#define OPCODE_ADDI   0b10010001000000000000000000000000
#define OPCODE_AND    0b10001010000000000000000000000000
#define OPCODE_ANDI   0b10010010000000000000000000000000
#define OPCODE_B      0b00010100000000000000000000000000
#define OPCODE_B_COND 0b01010100000000000000000000000000
#define OPCODE_BL     0b10010100000000000000000000000000
#define OPCODE_BR     0b11010110000000000000000000000000
#define OPCODE_CBNZ   0b10110101000000000000000000000000
#define OPCODE_CBZ    0b10110100000000000000000000000000
#define OPCODE_DUMP   0b11111111110000000000000000000000
#define OPCODE_EOR    0b11001010000000000000000000000000
#define OPCODE_EORI   0b11010010000000000000000000000000
#define OPCODE_HALT   0b11111111111000000000000000000000
#define OPCODE_LDUR   0b11111000010000000000000000000000
#define OPCODE_LDURB  0b00111000010000000000000000000000
#define OPCODE_LDURH  0b01111000010000000000000000000000
#define OPCODE_LDURSW 0b10111000100000000000000000000000
#define OPCODE_LSL    0b11010011011000000000000000000000
#define OPCODE_LSR    0b11010011010000000000000000000000
#define OPCODE_MUL    0b10011011000000000000000000000000
#define OPCODE_ORR    0b10101010000000000000000000000000
#define OPCODE_ORRI   0b10110010000000000000000000000000
#define OPCODE_PRNL   0b11111111100000000000000000000000
#define OPCODE_PRNT   0b11111111010000000000000000000000
#define OPCODE_SDIV   0b10011010110000000000000000000000
#define OPCODE_SMULH  0b10011011010000000000000000000000
#define OPCODE_STUR   0b11111000000000000000000000000000
#define OPCODE_STURB  0b00111000000000000000000000000000
#define OPCODE_STURH  0b01111000000000000000000000000000
#define OPCODE_STURW  0b10111000000000000000000000000000
#define OPCODE_SUB    0b11001011000000000000000000000000
#define OPCODE_SUBI   0b11010001000000000000000000000000
#define OPCODE_SUBIS  0b11110001000000000000000000000000
#define OPCODE_SUBS   0b11101011000000000000000000000000
#define OPCODE_UDIV   0b10011010110000000000000000000000
#define OPCODE_UMULH  0b10011011110000000000000000000000
// clang-format on

#define NUM_OPCODES 37

typedef struct instruction instruction_t;
typedef struct instruction {
  /* The implementaion function */
  void (*instruction_func)(uint64_t *, instruction_t *);

  union {
    uint32_t word;

    /* Schemas of different instruction formats */
    union {
      struct {
        uint32_t Rd : 5;
        uint32_t Rn : 5;
        uint32_t shamt : 6;
        uint32_t Rm : 5;
        uint32_t opcode : 11;
      } R;

      struct {
        uint32_t Rd : 5;
        uint32_t Rn : 5;
        uint32_t ALU_immediate : 12;
        uint32_t opcode : 10;
      } I;

      struct {
        uint32_t Rt : 5;
        uint32_t Rn : 5;
        uint32_t op : 2;
        uint32_t DT_address : 9;
        uint32_t opcode : 11;
      } D;

      struct {
        uint32_t BR_address : 26;
        uint32_t opcode : 6;
      } B;

      struct {
        uint32_t Rt : 5;
        uint32_t COND_BR_address : 19;
        uint32_t opcode : 8;
      } CB;

      struct {
        uint32_t Rd : 5;
        uint32_t MOV_immediate : 16;
        uint32_t opcode : 11;
      } IW;
    };
  };
} instruction_t;

typedef enum instruction_format {
  format_ERR,
  format_R,
  format_I,
  format_D,
  format_B,
  format_CB,
  format_IW
} instruction_format_t;

struct instruction_map {
  const uint32_t opcode;
  const instruction_format_t format;
  void (*instruction_func)(uint64_t *, instruction_t *);
};

/* Opcode tree node */
typedef struct node node_t;
typedef struct node {
  node_t *left, *right;
  unsigned data : 1;
  void (*instruction_func)(uint64_t *, instruction_t *);
} node_t;

/* Tree structure to detect opcodes and map to respective implementation
 * function.*/
typedef struct opcode_tree {
  node_t *root;
} opcode_tree_t;

/* Parses a word into the instruction_t structure */
instruction_t parse(uint32_t *word);

#endif
