#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

static const char *BASE58_ALPHABET = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

int base58_encode(const uint8_t *input, int input_length, char *output, int output_length) {
    int i, j;
    int zeros = 0;
    int length = 0;
    uint8_t *buffer = (uint8_t *)malloc(input_length * 2 + 1);

    if (!buffer) {
        return -1;
    }

    while (zeros < input_length && input[zeros] == 0) {
        zeros++;
    }

    memset(buffer, 0, input_length * 2 + 1);

    for (i = zeros; i < input_length; i++) {
        int carry = input[i];
        for (j = length; (carry != 0 || j < length) && j < input_length * 2; j++) {
            carry += 256 * buffer[j];
            buffer[j] = carry % 58;
            carry /= 58;
        }
        length = j;
    }

    for (i = 0; i < length / 2; i++) {
        uint8_t temp = buffer[i];
        buffer[i] = buffer[length - 1 - i];
        buffer[length - 1 - i] = temp;
    }

    for (i = 0; i < zeros; i++) {
        output[i] = '1';
    }

    for (j = 0; j < length; j++) {
        output[zeros + j] = BASE58_ALPHABET[buffer[j]];
    }

    output[zeros + length] = '\0';
    free(buffer);

    return zeros + length;
}

int base58_encode_check(const uint8_t *input, int input_length, char *output, int output_length) {
    uint8_t hash[SHA256_DIGEST_LENGTH];
    uint8_t *extended_input = (uint8_t *)malloc(input_length + 4);
    if (!extended_input) {
        return -1;
    }
    memcpy(extended_input, input, input_length);
    SHA256(input, input_length, hash);
    SHA256(hash, SHA256_DIGEST_LENGTH, hash);
    memcpy(extended_input + input_length, hash, 4);
    int result = base58_encode(extended_input, input_length + 4, output, output_length);
    free(extended_input);
    return result;
}
