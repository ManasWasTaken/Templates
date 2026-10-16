#include <bits/stdc++.h>
using namespace std;

#define int long long

int p;
int M;

int mod_pow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = (res * a) % M;
        a = (a * a) % M;
        b >>= 1;
    }
    return res;
}

vector<int> fact, invFact;

void precompute_factorials() {
    fact.resize(p);
    invFact.resize(p);

    fact[0] = 1;
    for (int i = 1; i < p; i++)
        fact[i] = (fact[i - 1] * i) % M;

    invFact[p - 1] = mod_pow(fact[p - 1], M - 2);
    for (int i = p - 2; i >= 0; i--)
        invFact[i] = (invFact[i + 1] * (i + 1)) % M;
}

int nCr_small(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[r] % M * invFact[n - r] % M;
}

int nCr_mod_p(int n, int r) {
    if (r > n) return 0;
    int res = 1;

    while (n > 0 || r > 0) {
        int ni = n % p;
        int ri = r % p;
        res = (res * nCr_small(ni, ri)) % p;
        n /= p;
        r /= p;
    }

    return res;
}

/*
Time Complexity of nCr_mod_p:
O(p + log_p(n))
p for factorial precomputation,
log_p(n) iterations inside Lucas loop
*/