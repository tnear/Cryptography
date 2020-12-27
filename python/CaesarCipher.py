# CaesarCipher.py
# Python Caesar cipher implementation which takes input string and a shift:
# >>> CaesarCipher.encrypt("abc", 2") => "cde"
# This implementation converts upper and lowercase letters while skipping others:
# >>> CaesarCipher.encrypt("a B", -1) => "z A"

def encrypt(input, shift):
    shift = int(shift) # work with integers
    ALPHA = 26
    shift %= ALPHA # restrict to alphabet size
    output = ""
    for char in input:
        value = ord(char) # integer representation of character
        if char.isalpha():
            zeroLetter = ord('a') if char.islower() else ord('A')
            normalized = value - zeroLetter # convert [0:25]
            normalized = (normalized + shift) % ALPHA  # Caesar Cipher encrypt
            normalized = (normalized + ALPHA) % ALPHA
            assert normalized >= 0 and normalized <= ALPHA
            value = normalized + zeroLetter

        output += chr(value) # concatenate
    return output
