# Base58 Encoding Project

This project provides implementations of Base58 encoding in both Python and C. Base58 is a binary-to-text encoding scheme used in Bitcoin and other cryptocurrencies. It's designed to be easily readable, avoid similar-looking characters, and be compatible with copy-paste.

## Contents

1. [Python Implementation](#python-implementation)
2. [C Implementation](#c-implementation)
3. [Usage](#usage)
4. [Building](#building)
5. [Dependencies](#dependencies)
6. [License](#license)

## Python Implementation

The Python implementation is contained in `base.py`. It provides functions for:

- Converting Base58 strings to bytes
- Converting bytes to Base58 strings
- Converting Base58 strings to WIF (Wallet Import Format)

## C Implementation

The C implementation is split into two files:

- `base58.h`: Header file with function declarations
- `base58.c`: Source file with function implementations

It provides functions for:

- Base58 encoding
- Base58 encoding with checksum (Base58Check)

## Usage

### Python

```python
from base import base58_to_wif

base58_string = '12XqeqZRVkBDgmPLVY4ZC6Y4ruUUEug8Fx'
mainnet_wif = base58_to_wif(base58_string, 0x80)
print(mainnet_wif)
```

### C

```c
#include "base58.h"

// Example usage
uint8_t input[] = {0x00, 0x01, 0x02, 0x03};
char output[100];
int length = base58_encode(input, sizeof(input), output, sizeof(output));
if (length > 0) {
    printf("Base58 encoded: %s\n", output);
}
```

## Building

### Python

No build step is required for the Python implementation. Ensure you have Python 3.x installed.

### C

To compile the C implementation, you'll need a C compiler and OpenSSL development libraries. On most Unix-like systems, you can compile it with:

```
gcc -c base58.c -o base58.o -lcrypto
```

## Dependencies

- Python implementation: No external dependencies
- C implementation: OpenSSL (libcrypto)

## License

MIT License

Copyright (c) 2024 [Your Name or Organization]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
