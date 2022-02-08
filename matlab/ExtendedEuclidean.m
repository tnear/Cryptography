% Extended Euclidean algorithm. Returns Bézout coefficients such that:
% aCoeff * a + bCoeff * b = gcd(a, b)
function [aCoeff, bCoeff, divisor] = ExtendedEuclidean(a, b)
    isint = isinteger(a) || isinteger(b);
    u = [1, 0, a];
    v = [0, 1, b];
    while v(3)
        if isint
            quotient = idivide(u(3), v(3));
        else
            quotient = fix(u(3) / v(3));
        end
        temp = u - v * quotient;
        u = v;
        v = temp;
    end

    aCoeff = u(1);
    bCoeff = u(2);
    divisor = u(3);
    if isint
        assert(int64(aCoeff) * int64(a) + int64(bCoeff) * int64(b) == divisor);
    else
        assert(aCoeff * a + bCoeff * b == divisor);
    end
end
