# AffineCipher.py
# An Affine cipher is a monoalphabetic substitution cipher which uses the formula
# ax + b (mod 26) to encrypt and
# a^-1 (x - b) (mod 26) to decrypt
# Decryption requires a^-1 to exist and throws an exception for invalid 'a'

import math
from enum import Enum

class TYPE(Enum):
    ENCRYPT = 0
    DECRYPT = 1

ALPHA = 26
NO_INVERSE = 0

def encrypt(input, a, b):
    a = int(a) % ALPHA # restrict inputs to [0:25]
    b = int(b) % ALPHA

    coprime = math.gcd(a, ALPHA) == 1
    if not coprime:
        raise Exception("a and b must be coprime for a to have an inverse")
    
    return _calculate(input, a, b, TYPE.ENCRYPT)
    
def decrypt(input, a, b):
    aInverse = _findInverse(a)
    if aInverse == NO_INVERSE:
        raise Exception("a has no inverse")

    return _calculate(input, aInverse, b, TYPE.DECRYPT)

def _findInverse(a):
    a %= ALPHA # ensure that number remains within int32 limit after multiplying below
    for i in range(ALPHA):
        # find 'i' which is multiplicative inverse of 'a'
        if (a * i) % ALPHA == 1:
            return i

    return NO_INVERSE

def _calculate(input, a, b, type):
    output = ""
    for char in input:
        value = ord(char) # integer representation of character
        if char.isalpha():
            zeroLetter = ord('a') if char.islower() else ord('A')
            normalized = value - zeroLetter # convert to range [0:25]
            if type == TYPE.ENCRYPT:
                normalized = (a * normalized + b) % ALPHA # Affine Cipher encrypt
            else:
                normalized = (a * (normalized - b)) % ALPHA # Affine Cipher decrypt

            normalized = (normalized + ALPHA) % ALPHA # restrict again to [0-25] in case of over/underflow
            assert normalized >= 0 and normalized <= ALPHA
            value = normalized + zeroLetter # after calculating, convert back to ascii letter range

        output += chr(value) # concatenate
    return output
