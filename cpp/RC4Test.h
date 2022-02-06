// RC4Test.h
// Test suite for RC4 stream cipher
// Contains positive tests for a variety of positive and negative input scenarios

#ifndef RC4_TEST_H
#define RC4_TEST_H

#include "RC4.h"
#include <cassert>

namespace RC4Test
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
            return; // correct exception
        }
        assert(false); // incorrect exception
    }

    void testEncryptDecrypt()
    {
        {
            // text and key same length
            RC4 rc4{ "123" };
            assert(rc4.encrypt("abc") == "3292dc");

            assert(rc4.decrypt(rc4.encrypt("abc")) == "abc");
        }

        {
            // text longer than key
            RC4 rc4{ "123" };
            assert(rc4.encrypt("abcd") == "3292dce6");

            assert(rc4.decrypt(rc4.encrypt("abcd")) == "abcd");
        }

        {
            // text shorter than key
            RC4 rc4{ "CDCD" };
            assert(rc4.encrypt("ab") == "10cf");

            assert(rc4.decrypt(rc4.encrypt("ab")) == "ab");
        }

        {
            // all alpha-numeric characters
            RC4 rc4{ "9876543210zyxwvutsrqponmlkjihgfedcbaZYXWVUTSRQPONMLKJIHGFEDCBA" };
            std::string txt = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
            std::string hexStr = "b9e5dde4862022699caa0be9cdc9d4829c62e83ed5778688bc25d3838aa016f0f7ea487b2cbea52a3a2a95571e591c0d260feebdf74fad8478c387cf09b0";
            assert(rc4.encrypt(txt) == hexStr);

            assert(rc4.decrypt(hexStr) == txt);
        }

        {
            // non-hex characters
            RC4 rc4{ "+_)(*&^%$#@!" };
            std::string expStr = "82c8cf505bbd33c5681211cd";
            assert(rc4.encrypt("!@#$%^&*()_+") == expStr);

            assert(rc4.decrypt(expStr) == "!@#$%^&*()_+");
        }
    }

    void testNegative()
    {
        {
            // odd-length ciphertext
            RC4 rc4{ "123" };
            assertException([&] { rc4.decrypt("abc"); });
        }

        {
            // non-hex ciphertext of even length
            RC4 rc4{ "+_)(" };
            assertException([&] { rc4.decrypt("!@#$"); });
        }
    }

    void testSuite()
    {
        testEncryptDecrypt();
        testNegative();
    }
}

#endif
