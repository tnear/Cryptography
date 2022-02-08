% Regression tests for the Extended Euclidean algorithm
% Uses MATLAB's built-in gcd() to verify accuracy
classdef ExtendedEuclideanTest < matlab.unittest.TestCase
    methods (Test)
        function t1(testCase)
            a = 1180;
            b = 482;
            verify(a, b, testCase);
        end

        function t2(testCase)
            a = 46;
            b = 240;
            verify(a, b, testCase);
        end

        function tFifty(testCase)
            for a = 1:50
                for b = 1:50
                    verify(a, b, testCase);
                end
            end
        end

        function tRandomSmall(testCase)
            for x = 1:1000
                a = randi([100, 10000]);
                b = randi([100, 10000]);
                verify(a, b, testCase);
            end
        end

        function tRandomMed(testCase)
            for x = 1:1000
                a = randi([100000, 10000000]);
                b = randi([100000, 10000000]);
                verify(a, b, testCase);
            end
        end

        function tRandomMedInt(testCase)
            for x = 1:1000
                a = randi([100000, 10000000], "int32");
                b = randi([100000, 10000000], "int32");
                verify(a, b, testCase);
            end
        end
    end
end

function verify(a, b, testCase)
    [aCoeff, bCoeff, divisor] = ExtendedEuclidean(a, b);
    [divAct, aAct, bAct] = gcd(a, b);
    testCase.assertEqual([aCoeff, bCoeff, divisor], [aAct, bAct, divAct], ...
        "Failed for a = " + a + " and b = " + b);
end
