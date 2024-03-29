function result = DiscreteLogarithm(a, b, m)
    % Discrete logarithm algorithm
    % Solves for 'result':
    %   a ^ result = b (mod m)

    result = 0;
    % slow: brute-force every number in range [1, m] using modular exponentiation
    for x = 1:m
        % modular exponentiation
        modulo = ModExp(a, x, m);
        if modulo == b
            % found
            result = x;
            break;
        end
    end
end
