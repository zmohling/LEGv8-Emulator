#ifndef READER_H_
#define READER_H_

#include <stdint.h>
#include <stdlib.h>

uint32_t* read_instructions(const char* filepath, unsigned long long*);

#endif
