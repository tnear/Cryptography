% Regression tests for Discrete Logarithm
classdef DiscreteLogarithmTest < matlab.unittest.TestCase
    methods (Test)
        function basic(testCase)
            testCase.verifyEqual(DiscreteLogarithm(5, 8, 13), 3);
            testCase.verifyEqual(DiscreteLogarithm(7, 15, 41), 3);
            testCase.verifyEqual(DiscreteLogarithm(5, 24, 37), 31);
            testCase.verifyEqual(DiscreteLogarithm(71, 151, 411), 28);
            testCase.verifyEqual(DiscreteLogarithm(76, 115, 223), 18);
            testCase.verifyEqual(DiscreteLogarithm(2051, 1331, 1451), 288);
            testCase.verifyEqual(DiscreteLogarithm(717, 1509, 9941), 8651);
            %testCase.verifyEqual(DiscreteLogarithm(844405, 3, 1898959), 8412);
            %testCase.verifyEqual(DiscreteLogarithm(100001, 67385023448517, 70606432933607), 5469654575878);
        end

        function gcdNot1(testCase)
            testCase.verifyEqual(DiscreteLogarithm(5, 4, 2), 0);
            testCase.verifyEqual(DiscreteLogarithm(10, 3, 4), 0);
            testCase.verifyEqual(DiscreteLogarithm(212, 11, 77), 0);
        end

        function other(testCase)
            testCase.verifyEqual(DiscreteLogarithm(5, 3, 2), 0);
            testCase.verifyEqual(DiscreteLogarithm(4, 1, 1), 0);
            testCase.verifyEqual(DiscreteLogarithm(1, 5, 5), 0);
        end
    end
end
