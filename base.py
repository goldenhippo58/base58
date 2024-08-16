import hashlib

def base58_to_bytes(base58_string):
    alphabet = '123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz'
    base58_bytes = 0
    for char in base58_string:
        base58_bytes = base58_bytes * 58 + alphabet.index(char)

    result = bytearray()
    while base58_bytes > 0:
        base58_bytes, remainder = divmod(base58_bytes, 256)
        result.insert(0, remainder)

    return bytes(result)

def bytes_to_base58(data):
    alphabet = '123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz'
    base58_string = ''
    value = int.from_bytes(data, byteorder='big')
    while value > 0:
        value, remainder = divmod(value, 58)
        base58_string = alphabet[remainder] + base58_string

    return base58_string

def base58_to_wif(base58_string, version_byte):
    # Decode Base58 to bytes
    decoded_bytes = base58_to_bytes(base58_string)

    # Remove version byte and checksum
    payload = decoded_bytes[1:-4]

    # Add version byte (0x80 for mainnet) and checksum
    extended_payload = bytes([version_byte]) + payload
    checksum = hashlib.sha256(hashlib.sha256(extended_payload).digest()).digest()[:4]
    wif_bytes = extended_payload + checksum

    # Encode as Base58
    wif = bytes_to_base58(wif_bytes)
    return wif

# Provided Base58 string
base58_string = '12XqeqZRVkBDgmPLVY4ZC6Y4ruUUEug8Fx'
mainnet_wif = base58_to_wif(base58_string, 0x80)
print(mainnet_wif)
