% Negative tests for the Extended Euclidean algorithm
classdef ExtendedEuclideanNegativeTest < matlab.unittest.TestCase
    methods (Test)
        function nargin(testCase)
            testCase.verifyError(@ExtendedEuclidean, "MATLAB:minrhs");
            testCase.verifyError(@() ExtendedEuclidean(1), "MATLAB:minrhs");
            testCase.verifyError(@() ExtendedEuclidean(1, 2, 3), "MATLAB:TooManyInputs");
            testCase.verifyError(@() ExtendedEuclidean(1, 2, 3, 4), "MATLAB:TooManyInputs");
        end

        function nargout(testCase)
            [~,~,~,~] = testCase.verifyError(@() ExtendedEuclidean(1, 2), "MATLAB:TooManyOutputs");
        end

        function unsigned(testCase)
            testCase.verifyError(@() ExtendedEuclidean(uint8(3), uint8(4)), "MATLAB:gcd:unsupportedType");
            testCase.verifyError(@() ExtendedEuclidean(uint16(3), uint16(4)), "MATLAB:gcd:unsupportedType");
            testCase.verifyError(@() ExtendedEuclidean(uint32(3), uint16(4)), "MATLAB:gcd:unsupportedType");
            testCase.verifyError(@() ExtendedEuclidean(uint64(3), uint64(4)), "MATLAB:gcd:unsupportedType");
        end

        function dimensions(testCase)
            testCase.verifyError(@() ExtendedEuclidean([1, 2], 3), "MATLAB:validation:IncompatibleSize");
            testCase.verifyError(@() ExtendedEuclidean(4, [5, 6]), "MATLAB:validation:IncompatibleSize");
            testCase.verifyError(@() ExtendedEuclidean([], 7), "MATLAB:validation:IncompatibleSize");
            testCase.verifyError(@() ExtendedEuclidean(8, []), "MATLAB:validation:IncompatibleSize");
            testCase.verifyError(@() ExtendedEuclidean(ones(1,1,2), 9), "MATLAB:validation:IncompatibleSize");
            testCase.verifyError(@() ExtendedEuclidean(10, ones(1,1,2)), "MATLAB:validation:IncompatibleSize");
        end

        function imag(testCase)
            testCase.verifyError(@() ExtendedEuclidean(1i, 0), "MATLAB:validators:mustBeReal");
            testCase.verifyError(@() ExtendedEuclidean(0, -1j), "MATLAB:validators:mustBeReal");
        end

        function inf(testCase)
            testCase.verifyError(@() ExtendedEuclidean(inf, 1), "MATLAB:validators:mustBeInteger");
            testCase.verifyError(@() ExtendedEuclidean(2, inf), "MATLAB:validators:mustBeInteger");
            testCase.verifyError(@() ExtendedEuclidean(-inf, 3), "MATLAB:validators:mustBeInteger");
            testCase.verifyError(@() ExtendedEuclidean(4, -inf), "MATLAB:validators:mustBeInteger");
        end

        function NaN(testCase)
            testCase.verifyError(@() ExtendedEuclidean(nan, 1), "MATLAB:validators:mustBeInteger");
            testCase.verifyError(@() ExtendedEuclidean(2, -nan), "MATLAB:validators:mustBeInteger");
        end

        function nonNumeric(testCase)
            testCase.verifyError(@() ExtendedEuclidean(seconds(3), 4), "MATLAB:validators:mustBeNumericOrLogical");
            testCase.verifyError(@() ExtendedEuclidean(1, NaT), "MATLAB:validators:mustBeNumericOrLogical");
            testCase.verifyError(@() ExtendedEuclidean(testCase, 4), "MATLAB:validators:mustBeNumericOrLogical");
            testCase.verifyError(@() ExtendedEuclidean({1}, {2}), "MATLAB:validators:mustBeNumericOrLogical");
        end

        function text(testCase)
            testCase.verifyError(@() ExtendedEuclidean('a', 'b'), "MATLAB:validators:mustBeNumericOrLogical");
            testCase.verifyError(@() ExtendedEuclidean("a", "b"), "MATLAB:validators:mustBeNumericOrLogical");
        end

        function fraction(testCase)
            testCase.verifyError(@() ExtendedEuclidean(1.1, 2), "MATLAB:validators:mustBeInteger");
            testCase.verifyError(@() ExtendedEuclidean(3, 4.4), "MATLAB:validators:mustBeInteger");
        end
    end
end
