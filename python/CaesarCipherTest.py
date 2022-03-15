# CaesarCipherTest.py
# Regression and performance tests for Caesar Cipher

import unittest
import CaesarCipher

# Benchmark:
# python -m timeit --setup "import CaesarCipher" "CaesarCipher.encrypt('abcdefghijklmnopqrstuvwxyz', 1)"
# 200000 loops, best of 5: 11.9 usec per loop

# Tests:
class CaesarCipherTest(unittest.TestCase):
    def testCaesarCipher(self):
        # empty string
        self.assertEqual(CaesarCipher.encrypt("", 0), "")
        # no shift
        self.assertEqual(CaesarCipher.encrypt("abc", 0), "abc")
        # 1-right
        self.assertEqual(CaesarCipher.encrypt("zabc", 1), "abcd")
        # 2-right
        self.assertEqual(CaesarCipher.encrypt("abc", 2), "cde")
        # 26-right (no shift)
        self.assertEqual(CaesarCipher.encrypt("abcd", 26), "abcd")
        # 1-left
        self.assertEqual(CaesarCipher.encrypt("bcd", -1), "abc")
        # 2-left (underflow)
        self.assertEqual(CaesarCipher.encrypt("abc", -2), "yza")
        # 30-left (underflow)
        self.assertEqual(CaesarCipher.encrypt("abc", -30), "wxy")
        # overflow, uppercase
        self.assertEqual(CaesarCipher.encrypt("TUVWXYZ", 15), "IJKLMNO")
        # underflow, uppercase
        self.assertEqual(CaesarCipher.encrypt("ABC", -2), "YZA")
        # mixed case
        self.assertEqual(CaesarCipher.encrypt("TestString", 23), "QbpqPqofkd")
        # 32-bit int min
        self.assertEqual(CaesarCipher.encrypt("AaZz", -2**31), "CcBb")
        # non-alphabet characters
        self.assertEqual(CaesarCipher.encrypt("aBc dEf. 123 ", 2), "cDe fGh. 123 ")
        # floating point
        self.assertEqual(CaesarCipher.encrypt("abc", 1.9), "bcd")

    def testNegative(self):
        self.assertRaises(ValueError, CaesarCipher.encrypt, "abc", "wrong_type")

if __name__ == '__main__':
    unittest.main()
