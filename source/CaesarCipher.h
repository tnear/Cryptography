// CaesarCipher.h
// C++ Caesar cipher implementation which takes input string and a shift
// >> encrypt("abc", 2") => "cde"
// This implementation converts upper and lowercase letters while skipping others
// >> encrypt("a b", -1) => "z a"
// Includes test suite testing various boundary conditions such as
// - empty string
// - positive, negative, zero, and maximum shift sizes
// - right shift were uppercase are shifted into ascii value of lowercase
// - mixed case, punctuation, and Unicode characters
// - also includes Google Benchmark performance metrics
#pragma once

#include <string>
#include <cassert>

namespace CaesarCipher
{
    // ----------------------------------------------------------
    // Benchmark                Time             CPU   Iterations
    // ----------------------------------------------------------
    // BM_CaesarCipher       69.8 ns         69.8 ns     11200000
    std::string encrypt(const std::string &input, int shift)
    {
        constexpr int ALPHA = 26;
        shift = shift % ALPHA;
        std::string output = input;
        for (char &ch : output)
        {
            if (!isalpha(ch))
                continue;

            if (islower(ch))
            {
                if (ch + shift < 'a')
                    ch += ALPHA;
                else if (ch + shift > 'z')
                    ch -= ALPHA;
            }
            else
            {
                assert(isupper(ch));
                if (ch + shift < 'A')
                    ch += ALPHA;
                else if (ch + shift > 'Z')
                    ch -= ALPHA;
            }
            
            ch += shift;
        }
        return output;
    }

    std::string decrypt(const std::string &input, int shift)
    {
        return encrypt(input, shift);
    }
};

void testEncrypt()
{
    std::string output;

    // empty
    output = CaesarCipher::encrypt("", 0);
    assert(output.empty());

    // no shift
    output = CaesarCipher::encrypt("abc", 0);
    assert(output == "abc");

    // 1-right
    output = CaesarCipher::encrypt("abc", 1);
    assert(output == "bcd");

    // 2-right
    output = CaesarCipher::encrypt("abc", 2);
    assert(output == "cde");

    // 26-right (no shift)
    output = CaesarCipher::encrypt("abcd", 0);
    assert(output == "abcd");

    // 1-left
    output = CaesarCipher::encrypt("bcd", -1);
    assert(output == "abc");

    // 2-left (underflow)
    output = CaesarCipher::encrypt("abc", -2);
    assert(output == "yza");

    // 30-left (underflow)
    output = CaesarCipher::encrypt("abc", -30);
    assert(output == "wxy");

    // overflow, uppercase
    output = CaesarCipher::encrypt("TUVWXYZ", 15);
    assert(output == "IJKLMNO");

    // underflow, uppercase
    output = CaesarCipher::encrypt("ABC", -2);
    assert(output == "YZA");

    // mixed case
    output = CaesarCipher::encrypt("TestString", 23);
    assert(output == "QbpqPqofkd");

    // boundary
    output = CaesarCipher::encrypt("AaZz", INT_MIN);
    assert(output == "CcBb");

    // unicode characters + testing small string optimization boundary (often ~16 characters)
    output = CaesarCipher::encrypt("aBc dEf. 123 aBc dEf. 123 aBc dEf. 123 aBc dEf. 123 aBc dEf. 123 ", 2);
    assert(output == "cDe fGh. 123 cDe fGh. 123 cDe fGh. 123 cDe fGh. 123 cDe fGh. 123 ");
}

void testDecrypt()
{
    std::string output = CaesarCipher::decrypt("QbpqPqofkd", -23);
    assert(output == "TestString");
}

void testSuite()
{
    testEncrypt();
    testDecrypt();
}
