% Performance tests for Affine Cipher
classdef AffineCipherBenchmark < matlab.perftest.TestCase
    methods(Test)
        %{
        To measure:
        results = runperf('AffineCipherBenchmark','ProcedureName','encryptPerformance');
        mean(results.Samples.MeasuredTime)
        % Duration: 3.9982e-05
        %}
        function encryptPerformance(testCase)
            while testCase.keepMeasuring
                AffineCipher.encrypt("abcdefghijklmnopqrstuvwxyz", 11, 13);
            end
        end

        %{
        results = runperf('AffineCipherBenchmark','ProcedureName','decryptPerformance');
        mean(results.Samples.MeasuredTime)
        % Duration: 5.1844e-05
        %}
        function decryptPerformance(testCase)
            while testCase.keepMeasuring
                AffineCipher.decrypt("abcdefghijklmnopqrstuvwxyz", 11, 13);
            end
        end
    end
end
