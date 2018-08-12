#include <cstdio>
 
typedef long long LL;
 
// return d = gcd(a, b) = ax + by
inline LL extended_euclid(const LL& a, const LL& b, LL &x, LL &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    LL d = extended_euclid(b, a % b, x, y);
    LL x1;
    x1 = x, x = y, y = x1 - a / b * y;
    return d;
}
  
inline LL modular_linear_equation_solver(const LL &a, const LL &b, const LL &n)
{
    LL d, x, y;
    d = extended_euclid(a, n, x, y);   
    if (b % d)
        return -1;
    LL x0 = x * (b / d) % n + n;   
    return x0 % (n / d);           
}
 
int main()
{
    LL A, B, C, k;
    while (~scanf("%lld%lld%lld%lld", &A, &B, &C, &k), A || B || C || k)
    {
        LL d = modular_linear_equation_solver(C, B - A, 1LL << k);
        if (d == -1)
            puts("FOREVER");
        else
            printf("%lld\n", d);
    }
    return 0;
}
