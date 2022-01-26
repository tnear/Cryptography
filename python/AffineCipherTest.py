# AffineCipherTest.py
# Benchmarking and regression tests for Affine cipher implemented in Python

import unittest
import AffineCipher

# Benchmark:
# Encrypt:
# python -m timeit --setup "import AffineCipher" "AffineCipher.encrypt('abcdefghijklmnopqrstuvwxyz', 11, 13)"
# 20000 loops, best of 5: 17.5 usec per loop

# Decrypt:
# python -m timeit --setup "import AffineCipher" "AffineCipher.decrypt('abcdefghijklmnopqrstuvwxyz', 11, 13)"
# 20000 loops, best of 5: 19 usec per loop

# Tests:
class AffineCipherTest(unittest.TestCase):
    def testEncrypt(self):
        # empty string
        a = 1
        self.assertEqual(AffineCipher.encrypt("", 1, 1), "")
        # no shift
        self.assertEqual(AffineCipher.encrypt("abc", 1, 0), "abc")
        # 1-right
        self.assertEqual(AffineCipher.encrypt("abc", 1, -1), "zab")
        # uppercase
        self.assertEqual(AffineCipher.encrypt("Y? Z A B!", 1, -4), "U? V W X!")
        # floating point
        self.assertEqual(AffineCipher.encrypt("xyz", 1.9, 3), "abc")
        # non-caesar shifts
        self.assertEqual(AffineCipher.encrypt("abc", 3, 1), "beh")
        # larger coprime than alphabet size
        self.assertEqual(AffineCipher.encrypt("Encrypt", 53, -54), "Clapwnr")
        # all letters
        self.assertEqual(AffineCipher.encrypt("abcdefghijklmnopqrstuvwxyz", 7, 14), "ovcjqxelszgnubipwdkryfmtah")
        # select 'a' where num*(alphabetSize-1) > int32 max (required to encrypt)
        self.assertEqual(AffineCipher.encrypt("Zyx", 214748377, 6), "Hij")

    def testDecrypt(self):
        # empty string
        self.assertEqual(AffineCipher.decrypt("", 1, 1), "")
        # caesar shift
        self.assertEqual(AffineCipher.decrypt("bcd", 1, 1), "abc")
        # affine shift with valid inverse
        self.assertEqual(AffineCipher.decrypt("fekhfm", 17, 20), "twenty")
        # all letters
        self.assertEqual(AffineCipher.decrypt("ovcjqxelszgnubipwdkryfmtah", 7, 14), "abcdefghijklmnopqrstuvwxyz")
        # mix of uppercase, lowercase, non-alphabetic characters
        self.assertEqual(AffineCipher.decrypt("Test 123!", 5, 255), "Khpk 123!")
        # 'a' outside alphabet range
        self.assertEqual(AffineCipher.decrypt("Abc", 29, 4), "Qzi")
        # select 'a' where num*(alphabetSize-1) > int32 max (required to decrypt)
        self.assertEqual(AffineCipher.decrypt("abc", 214748377, 1), "baz")

    def testNotCoprime(self):
        self.assertRaises(Exception, AffineCipher.encrypt, 2, 1)
        self.assertRaises(Exception, AffineCipher.encrypt, 13, -1)
        # larger 'a' than alphabet size
        self.assertRaises(Exception, AffineCipher.encrypt, 28, 3)

    def testNoInverse(self):
        # iterate over all numbers <=26 which have 2 or 13 as a prime factor
        # (based on factorization of alphabet=26 to 2&13)
        for a in [2, 4, 6, 8, 10, 12, 13, 14, 16, 18, 20, 22, 24, 26]:
            self.assertRaises(Exception, AffineCipher.decrypt, "a", a, 1)

        # number with no inverse outside alphabet range
        self.assertRaises(Exception, AffineCipher.decrypt, "a", 28, 28)

        # number with no inverse outside alphabet range
        self.assertRaises(Exception, AffineCipher.decrypt, "a", 0, 1)

if __name__ == '__main__':
    unittest.main()
