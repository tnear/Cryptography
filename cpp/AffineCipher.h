// AffineCipher.h
// An Affine cipher is a monoalphabetic substitution cipher which uses the formula
// ax + b (mod 26) to encrypt and
// a^-1 (x - b) (mod 26) to decrypt
// Decryption requires a^-1 to exist and throws an exception for invalid 'a'

#ifndef AFFINE_CIPHER_H
#define AFFINE_CIPHER_H

#include <string>
#include <cassert>

class AffineCipher
{
public:

    static std::string encrypt(const std::string &input, int a, int b)
    {
        a %= ALPHA; // restrict inputs to lowercase alphabet domain, [0:25]
        b %= ALPHA;

        const bool isCoprime = gcd(a, ALPHA) == 1;
        if (!isCoprime)
            throw std::exception("a must be coprime with alphabet size");

        return calculate(input, a, b, TYPE::ENCRYPT);
    }

    static std::string decrypt(const std::string &input, int a, int b)
    {
        const int aInverse = findInverse(a);
        if (aInverse == NO_INVERSE)
            throw std::exception("a has no inverse");

        return calculate(input, aInverse, b, TYPE::DECRYPT);
    }

private:
    enum class TYPE
    {
        ENCRYPT,
        DECRYPT
    };

    // Euclid's algorithm for greatest common divisor
    static constexpr int gcd(int a, int b)
    {
        if (b == 0)
            return a;
        return gcd(b, a % b);
    }

    // Modular multiplicative inverse definition:
    // a * a^-1 = 1 (mod m)
    static int findInverse(int a)
    {
        a %= ALPHA; // ensure that number remains within int32 limit after multiplying below
        for (int i = 0; i < ALPHA; ++i)
        {
            // find 'i' which is multiplicative inverse of 'a'
            if ((a * i) % ALPHA == 1)
                return i;
        }

        return NO_INVERSE;
    }

    static const std::string calculate(const std::string & input, int a, int b, TYPE type)
    {
        std::string output = input;
        for (char &ch : output)
        {
            if (!isalpha(ch))
                continue; // skip non-alphabetic characters

            const char zeroLetter = islower(ch) ? 'a' : 'A';
            char normalized = ch - zeroLetter; // convert to range [0:25]
            if (type == TYPE::ENCRYPT)
                normalized = (a * normalized + b) % ALPHA; // Affine Cipher encrypt
            else
                normalized = (a * (normalized - b)) % ALPHA; // Affine Cipher decrypt

            normalized = (normalized + ALPHA) % ALPHA; // restrict again to [0-25] in case of over/underflow
            assert(normalized >= 0 && normalized <= ALPHA);
            ch = normalized + zeroLetter; // after calculating, convert back to ascii letter range
        }

        return output;
    }

    static constexpr int ALPHA = 26;
    static constexpr int NO_INVERSE = 0;
};

#endif
