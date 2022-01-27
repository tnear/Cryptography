classdef AffineCipher
    % AffineCipher.m
    % An Affine cipher is a monoalphabetic substitution cipher which uses the formula
    % ax + b (mod 26) to encrypt and
    % a^-1 (x - b) (mod 26) to decrypt
    % Decryption requires a^-1 to exist and throws an exception for invalid 'a'
    properties (Constant)
        ALPHA = 26;
        NO_INVERSE = 0;
        ENCRYPT = 1;
        DECRYPT = 2;
    end

    methods (Static)
        function output = encrypt(input, a, b)
            arguments
                input (1,1) string;
                a (1,1) int32;
                b (1,1) int32;
            end

            a = mod(a, AffineCipher.ALPHA); % restrict input domain to [0:25]
            b = mod(b, AffineCipher.ALPHA);

            isCoprime = AffineCipher.gcdLocal(a, AffineCipher.ALPHA) == 1;
            if ~isCoprime
                errorStruct.message = 'a must be coprime with alphabet size.';
                errorStruct.identifier = 'Not:Coprime';
                error(errorStruct);
            end

            output = AffineCipher.calculate(input, a, b, AffineCipher.ENCRYPT);
        end

        function output = decrypt(input, a, b)
            arguments
                input (1,1) string;
                a (1,1) int32;
                b (1,1) int32;
            end

            aInverse = AffineCipher.findInverse(a);
            output = AffineCipher.calculate(input, aInverse, b, AffineCipher.DECRYPT);
        end
    end

    methods (Static, Access=private)
        % Modular multiplicative inverse definition:
        % a * a^-1 = 1 (mod m)
        function aInverse = findInverse(a)
            arguments
                a double;
            end
            [a, U] = gcd(a, AffineCipher.ALPHA);
            if a == 1
                aInverse = mod(U, AffineCipher.ALPHA);
            else
                errorStruct.message = 'a has no inverse.';
                errorStruct.identifier = 'No:Inverse';
                error(errorStruct);
            end
        end

        function output = calculate(input, a, b, type)
            ascii = int32(input{1});
            % identify upper and lowercase letters
            upperMask = isstrprop(ascii, 'upper');
            lowerMask = isstrprop(ascii, 'lower');
            letterMask = upperMask | lowerMask;
            zeroLetters = zeros([1, input.strlength], 'int32');
            zeroLetters(upperMask) = int32('A');
            zeroLetters(lowerMask) = int32('a');

            % make letters zero-indexed
            normalized = ascii - zeroLetters;
            % Affine cipher algorithm
            if type == AffineCipher.ENCRYPT
                normalized = mod(a * normalized + b, AffineCipher.ALPHA);
            else
                normalized = mod(a * (normalized - b), AffineCipher.ALPHA);
            end

            normalized = mod(normalized + AffineCipher.ALPHA, AffineCipher.ALPHA);
            assert(all(normalized >= 0 & normalized <= AffineCipher.ALPHA));
            ascii = normalized + zeroLetters;
            output = char(ascii);
            % copy non-letters from input to output
            output(~letterMask) = input{1}(~letterMask);
            output = string(output);
        end

        % faster version of gcd() without error checking
        function d = gcdLocal(a, b)
            if b == 0
                d = a;
            else
                d = AffineCipher.gcdLocal(b, mod(a, b));
            end
        end
    end
end
