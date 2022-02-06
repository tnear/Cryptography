% Extended Euclidean algorithm. Returns Bézout coefficients such that:
% aCoeff * a + bCoeff * b = gcd(a, b)
function [aCoeff, bCoeff, divisor] = ExtendedEuclidean(a, b)
    u = [1, 0, a];
    v = [0, 1, b];
    while v(3)
        quotient = fix(u(3) / v(3));
        temp = u - v * quotient;
        u = v;
        v = temp;
    end

    aCoeff = u(1);
    bCoeff = u(2);
    divisor = u(3);
    assert(aCoeff * a + bCoeff * b == divisor);
end
