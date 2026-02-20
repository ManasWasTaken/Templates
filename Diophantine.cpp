#include <bits/stdc++.h>
using namespace std;

#define int long long

// Solve linear Diophantine equation:
// a*x + b*y = c

// A solution exists iff gcd(a,b) | c

// If (x0, y0) is one solution, then ALL solutions are:
// x = x0 + (b/g)*t
// y = y0 - (a/g)*t   for any integer t

long long ext_gcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    long long x1, y1;
    long long g = ext_gcd(b, a % b, x1, y1);

    x = y1;
    y = x1 - y1 * (a / b);

    return g;
}

// Finds ONE solution (x, y) to a*x + b*y = c
// Returns false if no solution exists

bool diophantine(long long a, long long b, long long c,
                 long long &x, long long &y) {

    long long g = ext_gcd(a, b, x, y);

    if (c % g != 0)
        return false;

    x *= c / g;
    y *= c / g;

    return true;
}