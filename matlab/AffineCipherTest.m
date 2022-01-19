% Affine cipher regression tests
classdef AffineCipherTest < matlab.unittest.TestCase
    methods(Test)
        function testEncrypt(testCase)
            testCase.assertEqual(AffineCipher.encrypt("", 1, 1), "");
            testCase.assertEqual(AffineCipher.encrypt("abc", 1, 1), "bcd");
            testCase.assertEqual(AffineCipher.encrypt("abc", 1, 3), "def");
            testCase.assertEqual(AffineCipher.encrypt("BCD", 1, -1), "ABC");
            testCase.assertEqual(AffineCipher.encrypt("yza", 1, 4), "cde");
            testCase.assertEqual(AffineCipher.encrypt("Y? Z A B!", 1, -4), "U? V W X!");
            testCase.assertEqual(AffineCipher.encrypt("abcdefghijklmnopqrstuvwxyz", 11, 13), "nyjufqbmxitepalwhsdozkvgrc");
        end

        function testDecrypt(testCase)
            testCase.assertEqual(AffineCipher.decrypt("", 1, 1), "");
            testCase.assertEqual(AffineCipher.decrypt("bcd", 1, 1), "abc");
            testCase.assertEqual(AffineCipher.decrypt("fekhfm", 17, 20), "twenty");
            testCase.assertEqual(AffineCipher.decrypt("ovcjqxelszgnubipwdkryfmtah", 7, 14), "abcdefghijklmnopqrstuvwxyz");
            testCase.assertEqual(AffineCipher.decrypt("Test 123!", 5, 255), "Khpk 123!");
            testCase.assertEqual(AffineCipher.decrypt("Abc", 29, 4), "Qzi");
            testCase.assertEqual(AffineCipher.decrypt("abc", 214748377, 1), "baz");
        end

        function testNotCoprime(testCase)
            testCase.assertError(@() AffineCipher.encrypt("a", 2, 1), "Not:Coprime");
            testCase.assertError(@() AffineCipher.encrypt("a", 13, -1), "Not:Coprime");
            testCase.assertError(@() AffineCipher.encrypt("a", 28, 3), "Not:Coprime");
        end

        function testNoInverse(testCase)
            for a = [2, 4, 6, 8, 10, 12, 13, 14, 16, 18, 20, 22, 24, 26]
                testCase.assertError(@() AffineCipher.decrypt("a", a, 1), "No:Inverse");
            end

            testCase.assertError(@() AffineCipher.decrypt("a", 28, 28), "No:Inverse");
            testCase.assertError(@() AffineCipher.decrypt("a", 0, 1), "No:Inverse");
        end
    end
end
