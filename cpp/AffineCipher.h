// AffineCipher.h
#pragma once

#include <string>
#include <cassert>

namespace AffineCipher
{
    // Euclid's algorithm for greatest common divisor
    constexpr int gcd(int a, int b)
    {
        if (b == 0)
            return a;
        return gcd(b, a % b);
    }

    constexpr bool isCoprime(int a, int b)
    {
        return gcd(a, b) == 1;
    }

    std::string encrypt(const std::string &input, int a, int b)
    {
        constexpr int ALPHA = 26;
        if (!isCoprime(a, ALPHA))
            throw std::exception("a must be coprime with alphabet size");

        b %= ALPHA; // restrict to [0:25]

        std::string output = input;
        for (char &ch : output)
        {
            if (!isalpha(ch))
                continue; // do not shift non-alphabetic characters

            const char zeroLetter = islower(ch) ? 'a' : 'A';
            char normalized = ch - zeroLetter; // convert [0:25]
            normalized = (a * normalized + b) % ALPHA; // Affine Cipher Encrypt
            normalized = (normalized + ALPHA) % ALPHA; // restrict again [0-25] in case of over/underflow
            assert(normalized >= 0 && normalized <= ALPHA);
            ch = normalized + zeroLetter;

        }
        return output;
    }

    int findInverse(int a, int b)
    {
        return a;
    }

    std::string decrypt(const std::string &input, int a, int b)
    {
        constexpr int ALPHA = 26;
        //const int a = findInverse(b, ALPHA);
        const int aInverse = findInverse(a, ALPHA);
        std::string output = input;
        for (char &ch : output)
        {
            if (!isalpha(ch))
                continue; // do not shift non-alphabetic characters

            const char zeroLetter = islower(ch) ? 'a' : 'A';
            char normalized = ch - zeroLetter; // convert [0:25]
            normalized = (aInverse * (normalized - b)) % ALPHA; // Affine Cipher Decrypt
            normalized = (normalized + ALPHA) % ALPHA; // restrict again [0-25] in case of over/underflow
            assert(normalized >= 0 && normalized <= ALPHA);
            ch = normalized + zeroLetter;

        }

        return output;
    }
}

namespace AffineCipher
{
    template <typename Func>
    void assertException(Func func)
    {
        try
        {
            func();
        }
        catch (const std::exception &)
        {
            return;
        }
        assert(false); // incorrect exception
    }

    void testNotCoprime()
    {
        assertException([] { AffineCipher::encrypt("a", 2, 1); });
        assertException([] { AffineCipher::encrypt("a", 13, -1); });
    }

    void testCaesar()
    {
        std::string output;
        // empty
        output = AffineCipher::encrypt("", 1, 1);
        assert(output.empty());

        // Caesar cipher (1-right)
        output = AffineCipher::encrypt("abc", 1, 1);
        assert(output == "bcd");

        // Caesar cipher (3-left)
        output = AffineCipher::encrypt("abc", 1, 3);
        assert(output == "def");

        // Caesar cipher (1-left)
        output = AffineCipher::encrypt("bcd", 1, -1);
        assert(output == "abc");

        // Caesar cipher (3-left, underflow)
        output = AffineCipher::encrypt("abc", 1, -3);
        assert(output == "xyz");

        // Caesar cipher (4-right, overflow)
        output = AffineCipher::encrypt("yza", 1, 4);
        assert(output == "cde");

        // Caesar cipher (uppercase)
        output = AffineCipher::encrypt("Y? Z A B!", 1, -4);
        assert(output == "U? V W X!");
    }

    void testEncrypt()
    {
        std::string output;
        output = AffineCipher::encrypt("abc", 3, 1);
        assert(output == "beh");

        output = AffineCipher::encrypt("test TEST", 19, 4);
        assert(output == "bcib BCIB");

        // larger coprime than alphabet size
        output = AffineCipher::encrypt("Encrypt", 53, -54);
        assert(output == "Clapwnr");
    }

    void testDecrypt()
    {
        std::string output;
        // empty
        output = AffineCipher::decrypt("", 1, 1);
        assert(output.empty());

        output = AffineCipher::decrypt("bcd", 1, 1);
        assert(output == "abc");
    }

    void testSuite()
    {
        testNotCoprime();
        testCaesar();
        testEncrypt();
        testDecrypt();
    }
};
