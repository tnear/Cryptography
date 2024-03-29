% Regression tests for the Extended Euclidean algorithm
% Uses MATLAB's built-in gcd() to verify accuracy
classdef ExtendedEuclideanTest < matlab.unittest.TestCase
    methods (Test)
        function tiny(testCase)
            a = 46;
            b = 240;
            verify(a, b, testCase);
        end

        function tiny2(testCase)
            a = 1180;
            b = 482;
            verify(a, b, testCase);
        end

        function sparse(testCase)
            a = sparse(3);
            b = sparse(6);
            verify(a, b, testCase);
        end

        function logical(testCase)
            verify(true, true, testCase);
            verify(true, false, testCase);
            verify(false, true, testCase);
            verify(false, false, testCase);
        end

        function fiftyNested(testCase)
            for a = 1:50
                for b = 1:50
                    verify(a, b, testCase);
                end
            end
        end

        function negative(testCase)
            num = 15;
            for a = 1:num
                for b = -1:-1:-num
                    verify(a, b, testCase);
                end
            end

            for a = -1:-1:-num
                for b = 1:1:num
                    verify(a, b, testCase);
                end
            end

            for a = -1:-1:-num
                for b = -1:-1:-num
                    verify(a, b, testCase);
                end
            end
        end

        function negativeInt(testCase)
            num = int32(15);
            for a = -1:-1:-num
                for b = -1:-1:-num
                    verify(a, b, testCase);
                end
            end
        end

        function randomSmall(testCase)
            for x = 1:1000
                a = randi([100, 10000]);
                b = randi([100, 10000]);
                verify(a, b, testCase);
            end
        end

        function randomMed(testCase)
            for x = 1:1000
                a = randi([100000, 10000000]);
                b = randi([100000, 10000000]);
                verify(a, b, testCase);
            end
        end

        function randomMedInt32(testCase)
            for x = 1:1000
                a = randi([100000, 10000000], "int32");
                b = randi([100000, 10000000], "int32");
                verify(a, b, testCase);
            end
        end

        function negativeRandomMedInt32(testCase)
            for x = 1:1000
                a = -randi([100000, 10000000], "int32");
                b = -randi([100000, 10000000], "int32");
                a = a + mod(a, 2) + 1; % ensure odd
                b = b + mod(b, 2) + 1;
                verify(a, b, testCase);
            end
        end

        function E40(testCase)
            for x = 1:1000
                a = randi([2^30, 2^40]);
                b = randi([2^30, 2^40]);
                verify(a, b, testCase);
            end
        end

        function E50(testCase)
            for x = 1:1000
                a = randi([2^40, 2^50]);
                b = randi([2^40, 2^50]);
                verify(a, b, testCase);
            end
        end

        % randi max range
        function E53(testCase)
            for x = 1:1000
                a = randi([2^51, 2^53 - 1]);
                b = randi([2^51, 2^53 - 1]);
                verify(a, b, testCase);
            end
        end

        function largestFlint(testCase)
            % double
            testCase.verifyWarning(@() ExtendedEuclidean(2^54, 2), "MATLAB:gcd:largestFlint");
            testCase.verifyWarning(@() ExtendedEuclidean(2, 2^54), "MATLAB:gcd:largestFlint");
            testCase.verifyWarning(@() ExtendedEuclidean(-2^54, -2), "MATLAB:gcd:largestFlint");
            testCase.verifyWarning(@() ExtendedEuclidean(-2, 2^54), "MATLAB:gcd:largestFlint");
            % single
            testCase.verifyWarning(@() ExtendedEuclidean(single(2)^25, single(2)), "MATLAB:gcd:largestFlint");
            testCase.verifyWarning(@() ExtendedEuclidean(single(2), 2^25), "MATLAB:gcd:largestFlint");
            testCase.verifyWarning(@() ExtendedEuclidean(-single(2)^25, -single(2)), "MATLAB:gcd:largestFlint");
            testCase.verifyWarning(@() ExtendedEuclidean(single(2), 2^25), "MATLAB:gcd:largestFlint");
        end

        function E64(testCase)
            testCase.applyFixture( ...
                matlab.unittest.fixtures.SuppressedWarningsFixture( ...
                "MATLAB:gcd:largestFlint"));

            for x = 1:500
                a = 2^64 - randi(2^53 - 1);
                b = 2^64 - randi(2^53 - 1);
                verify(a, b, testCase);
            end
        end

        function I63(testCase)
            testCase.applyFixture( ...
                matlab.unittest.fixtures.SuppressedWarningsFixture( ...
                "MATLAB:gcd:largestFlint"));

            for x = 1:500
                a = int64(2)^63 - randi([1, 100]) * randi(2^53 - 1);
                b = int64(2)^63 - randi([1, 100]) * randi(2^53 - 1);
                verify(a, b, testCase);
            end
        end

        function realMax(testCase)
            testCase.applyFixture( ...
                matlab.unittest.fixtures.SuppressedWarningsFixture( ...
                "MATLAB:gcd:largestFlint"));

            verify(realmax, realmax, testCase);
            for x = 1:500
                a = realmax * rand;
                b = realmax * rand;
                verify(a, b, testCase);
            end
        end
    end
end

function verify(a, b, testCase)
    try
        [aCoeff, bCoeff, divisor] = ExtendedEuclidean(a, b);
    catch me
        disp(me);
    end
    [divAct, aAct, bAct] = gcd(a, b);

    if issparse(a) || issparse(b)
        a = full(a);
        b = full(b);
    end

    testCase.assertEqual([aCoeff, bCoeff, divisor], [aAct, bAct, divAct], ...
        "Failed for a = " + a + " and b = " + b);
end
