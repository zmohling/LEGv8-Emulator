#ifndef PARSER_H_
#define PARSER_H_

#include <stdint.h>

#define OPCODE_ADD 0b10001011000
#define OPCODE_ADDI 0b1001000100
#define OPCODE_AND 0b10001010000
#define OPCODE_ANDI 0b1001001000
#define OPCODE_B 0b000101
#define OPCODE_B_COND 0b01010100
#define OPCODE_BL 0b100101
#define OPCODE_BR 0b11010110000
#define OPCODE_CBNZ 0b10110101
#define OPCODE_CBZ 0b10110100
#define OPCODE_DUMP 0b11111111110
#define OPCODE_EOR 0b11001010000
#define OPCODE_EORI 0b1101001000
#define OPCODE_HALT 0b11111111111
#define OPCODE_LDUR 0b11111000010

typedef struct r_format {
  uint16_t opcode : 11;
  uint8_t Rm : 5;
  uint8_t shamt : 6;
  uint8_t Rn : 5;
  uint8_t Rd : 5;
} r_format_t;

typedef struct i_format {
  uint16_t opcode : 10;
  uint16_t ALU_immediate : 12;
  uint8_t Rn : 5;
  uint8_t Rd : 5;
} i_format_t;

typedef struct d_format {
  uint16_t opcode : 11;
  uint16_t DT_address : 9;
  uint8_t op : 2;
  uint8_t Rn : 5;
  uint8_t Rt : 5;
} d_format_t;

typedef struct b_format {
  uint8_t opcode : 6;
  uint32_t BR_address : 26;
} b_format_t;

typedef struct cb_format {
  uint8_t opcode : 8;
  uint32_t COND_BR_address : 19;
  uint16_t Rt : 5;
} cb_format_t;

typedef struct iw_format {
  uint16_t opcode : 11;
  uint16_t MOV_immediate : 16;
  uint8_t Rd : 5;
} iw_format_t;

union instruction_formats {
  r_format_t r;
  i_format_t i;
  d_format_t d;
  b_format_t b;
  cb_format_t cb;
  iw_format_t iw;
} instruction;

#endif
