#include "utils.h"

float mapLine(float val, float xa, float ya, float xb, float yb)
{
    float m = (yb - ya) / (xb - xa);
    float p = ya - m * xa;

    return m * val + p;
}

float dist(float xa, float ya, float xb, float yb)
{
    return std::sqrt(std::pow(xb - xa, 2) + std::pow(yb - ya, 2));
}

float factorial(float nb)
{
    if (nb <= 0) return 0;

    float r = nb;

    for (int i = nb - 1; i > 1; i--)
        r *= i;
    return r;
}

float countCombinations(float k, float n)
{
    return factorial(n) / (factorial(k) * factorial(n - k));
}
