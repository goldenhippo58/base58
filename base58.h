#ifndef BASE58_H
#define BASE58_H

#include <stdint.h>

int base58_encode(const uint8_t *input, int input_length, char *output, int output_length);
int base58_encode_check(const uint8_t *input, int input_length, char *output, int output_length);

#endif
