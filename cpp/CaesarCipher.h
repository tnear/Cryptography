// CaesarCipher.h
// C++ Caesar cipher implementation which takes input string and a shift:
// CaesarCipher::encrypt("abc", 2") => "cde"
// This implementation converts upper and lowercase letters while skipping others:
// CaesarCipher::encrypt("a B", -1) => "z A"

#pragma once

#include <string>

namespace CaesarCipher
{
    std::string encrypt(const std::string &input, int shift)
    {
        constexpr int ALPHA = 26;
        shift %= ALPHA; // restrict to [0-25]
        std::string output = input;
        for (char &ch : output)
        {
            if (!isalpha(ch))
                continue; // do not shift non-alphabetic characters

            const char zeroLetter = islower(ch) ? 'a' : 'A';
            char normalized = ch - zeroLetter; // convert [0:25]
            normalized = (normalized + shift) % ALPHA; // Caesar Cipher encrypt
            normalized = (normalized + ALPHA) % ALPHA; // restrict again [0-25] in case of over/underflow
            assert(normalized >= 0 && normalized <= ALPHA);
            ch = normalized + zeroLetter;
        }
        return output;
    }

    std::string decrypt(const std::string &input, int shift)
    {
        return encrypt(input, shift);
    }
}
