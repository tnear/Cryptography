% Extended Euclidean algorithm. Returns Bézout coefficients such that:
% aCoeff * a + bCoeff * b = gcd(a, b)
function [aCoeff, bCoeff, divisor] = ExtendedEuclidean(a, b)
    arguments
        a (1,1) {mustBeInteger};
        b (1,1) {mustBeInteger};
    end
    isint = isinteger(a) || isinteger(b);
    if isint
        isunsigned = intmin(class(a)) == 0 || intmin(class(b)) == 0;
        if isunsigned
            error(message('MATLAB:gcd:unsupportedType'));
        end
    else
        classin = superiorfloat(a, b);
        largestFlint = flintmax(classin);
        if abs(a) > largestFlint || abs(b) > largestFlint
            warning(message('MATLAB:gcd:largestFlint'));
        end
    end

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
    aCoeff = aCoeff * sign(divisor);
    bCoeff = bCoeff * sign(divisor);
    divisor = abs(divisor);
    %assert(int64(aCoeff) * int64(a) + int64(bCoeff) * int64(b) == int64(divisor));
end
