// Test suite for various boundary conditions such as
// - empty string
// - positive, negative, zero, and maximum shift sizes
// - right shift were uppercase are shifted into ascii value of lowercase
// - mixed case and punctuation


/* Benchmark:
----------------------------------------------------------
Benchmark                Time             CPU   Iterations
----------------------------------------------------------
BM_CaesarCipher        324 ns          322 ns      2133333

static void BM_CaesarCipher(benchmark::State &state)
{
    for (auto _ : state)
    {
        CaesarCipher::encrypt("abcdefghijklmnopqrstuvwxyz", 1);
    }
}
BENCHMARK(BM_CaesarCipher);
*/

#ifndef CAESAR_CIPHER_TEST_H
#define CAESAR_CIPHER_TEST_H

#include <string>
#include <cassert>
#include "CaesarCipher.h"

namespace CaesarCipher
{
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
        output = CaesarCipher::encrypt("abcd", 26);
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

        // non-alphabet characters + testing small string optimization boundary (often ~16 characters)
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
};

#endif
