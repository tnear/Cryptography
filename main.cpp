// main.cpp

#include <iostream>
#include "cpp/RC4Test.h"
#include <numeric>
#include <inttypes.h>
#define nelems(x) (sizeof(x) / sizeof((x)[0]))

const int multiplier[] = { 1, 3, 5, 7, 11, 3 * 5, 3 * 7, 3 * 11, 5 * 7, 5 * 11, 7 * 11, 3 * 5 * 7, 3 * 5 * 11, 3 * 7 * 11, 5 * 7 * 11, 3 * 5 * 7 * 11 };

uint64_t SQUFOF(uint64_t N)
{
    uint64_t D, Po, P, Pprev, Q, Qprev, q, b, r, s;
    uint32_t L, B, i;
    s = (uint64_t)(sqrtl(N) + 0.5);
    if (s * s == N)
        return s;

    for (int k = 0; k < nelems(multiplier) && N <= UINT64_MAX / multiplier[k]; k++)
    {
        D = multiplier[k] * N;
        Po = Pprev = P = sqrtl(D);
        Qprev = 1;
        Q = D - Po * Po;
        L = 2 * sqrtl(2 * s);
        B = 3 * L;
        for (i = 2; i < B; i++)
        {
            b = (uint64_t)((Po + P) / Q);
            P = b * Q - P;
            q = Q;
            Q = Qprev + b * (Pprev - P);
            r = (uint64_t)(sqrtl(Q) + 0.5);
            if (!(i & 1) && r * r == Q)
            {
                //std::cout << r << '\n';
                break;
            }
            Qprev = q;
            Pprev = P;
        };
        if (i >= B)
            continue;

        b = (uint64_t)((Po - P) / r);
        Pprev = P = b * r + P;
        Qprev = r;
        Q = (D - Pprev * Pprev) / Qprev;
        i = 0;
        do
        {
            b = (uint64_t)((Po + P) / Q);
            Pprev = P;
            P = b * Q - P;
            q = Q;
            Q = Qprev + b * (Pprev - P);
            Qprev = q;
            i++;
        } while (P != Pprev);
        r = std::gcd(N, Qprev);

        if (r != 1 && r != N)
            return r;
    }
    return 0;
}

int main()
{
    RC4Test::testSuite();
    std::cout << "Tests passed!\n";

    auto result = SQUFOF(5214317);
    std::cout << '\n' << result << '\n';
}
