// AffineCipherTest.h
// Benchmarking and test cases for Affine cipher

/* Benchmark:
-----------------------------------------------------------------
Benchmark                       Time             CPU   Iterations
-----------------------------------------------------------------
BM_AffineCipherEncrypt        326 ns          330 ns      2133333
BM_AffineCipherDecrypt        366 ns          369 ns      1947826

static void BM_AffineCipherEncrypt(benchmark::State &state)
{
    for (auto _ : state)
    {
        AffineCipher::encrypt("abcdefghijklmnopqrstuvwxyz", 11, 13);
    }
}
BENCHMARK(BM_AffineCipherEncrypt);

static void BM_AffineCipherDecrypt(benchmark::State &state)
{
    for (auto _ : state)
    {
        AffineCipher::decrypt("abcdefghijklmnopqrstuvwxyz", 11, 13);
    }
}
BENCHMARK(BM_AffineCipherDecrypt);
*/

#ifndef AFFINE_CIPHER_TEST_H
#define AFFINE_CIPHER_TEST_H

#include "AffineCipher.h"
#include <string>
#include <cassert>

template <typename Func>
void assertException(Func func)
{
    try
    {
        func();
    }
    catch (const std::exception &)
    {
        return; // correct exception
    }
    assert(false); // incorrect exception
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

    // all letters
    output = AffineCipher::encrypt("abcdefghijklmnopqrstuvwxyz", 7, 14);
    assert(output == "ovcjqxelszgnubipwdkryfmtah");

    // select 'a' where num*(alphabetSize-1) > int32 max (required to encrypt)
    output = AffineCipher::encrypt("Zyx", 214748377, 6);
    assert(output == "Hij");
}

void testDecrypt()
{
    std::string output;

    // empty
    output = AffineCipher::decrypt("", 1, 1);
    assert(output.empty());

    output = AffineCipher::decrypt("bcd", 1, 1);
    assert(output == "abc");

    output = AffineCipher::decrypt("fekhfm", 17, 20);
    assert(output == "twenty");

    // all letters
    output = AffineCipher::decrypt("ovcjqxelszgnubipwdkryfmtah", 7, 14);
    assert(output == "abcdefghijklmnopqrstuvwxyz");

    // mix of uppercase, lowercase, non-alphabetic characters
    output = AffineCipher::decrypt("Test 123!", 5, 255);
    assert(output == "Khpk 123!");

    // 'a' outside alphabet range
    output = AffineCipher::decrypt("Abc", 29, 4);
    assert(output == "Qzi");

    // select 'a' where num*(alphabetSize-1) > int32 max (required to decrypt)
    output = AffineCipher::decrypt("abc", 214748377, 1);
    assert(output == "baz");
}

void testNotCoprime()
{
    assertException([] { AffineCipher::encrypt("a", 2, 1); });
    assertException([] { AffineCipher::encrypt("a", 13, -1); });
    assertException([] { AffineCipher::encrypt("a", 28, 3); });
}

void testNoInverse()
{
    // iterate over all numbers <=26 which have 2 or 13 as a prime factor
    // (based on factorization of alphabet=26 to 2&13)
    for (int a : { 2, 4, 6, 8, 10, 12, 13, 14, 16, 18, 20, 22, 24, 26 })
    {
        assertException([a] { AffineCipher::decrypt("a", a, 1); });
    }

    // number with no inverse outside alphabet range
    assertException([] { AffineCipher::decrypt("a", 28, 28); });

    // number with no inverse outside alphabet range
    assertException([] { AffineCipher::decrypt("a", 0, 1); });
}

void testSuite()
{
    testCaesar();
    testEncrypt();
    testDecrypt();
    testNotCoprime();
    testNoInverse();
}

#endif
