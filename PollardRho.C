#include <bits/stdc++.h>
using namespace std;

#define int long long

static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// Safe modular multiplication (no overflow using repeated addition)
int mulmod(int a, int b, int mod) {
    int res = 0;
    a %= mod; b %= mod;
    while (b > 0) {
        if (b & 1) res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

// Modular exponentiation
int pow_mod(int a, int e, int mod) {
    int r = 1;
    a %= mod;
    while (e > 0) {
        if (e & 1) r = mulmod(r, a, mod);
        a = mulmod(a, a, mod);
        e >>= 1;
    }
    return r;
}

// Miller–Rabin primality test
bool is_prime(int n) {
    if (n < 2) return false;
    for (int p : {2,3,5,7,11,13,17,19,23,29,31,37}) {
        if (n % p == 0) return n == p;
    }

    int d = n - 1, s = 0;
    while ((d & 1) == 0) d >>= 1, s++;

    auto check = [&](int a) -> bool {
        if (a % n == 0) return true;
        int x = pow_mod(a, d, n);
        if (x == 1 || x == n - 1) return true;
        for (int r = 1; r < s; ++r) {
            x = mulmod(x, x, n);
            if (x == n - 1) return true;
        }
        return false;
    };

    for (int a : {2,3,5,7,11,13,17,19,23,29,31,37})
        if (!check(a)) return false;

    return true;
}

// Pollard's Rho function
int pollard_rho(int n) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;

    uniform_int_distribution<int> dist_c(1, n - 1);
    uniform_int_distribution<int> dist_x(2, n - 2);
    auto f = [&](int x, int c) { return (mulmod(x, x, n) + c) % n; };

    while (true) {
        int x = dist_x(rng), y = x, c = dist_c(rng), d = 1;
        while (d == 1) {
            x = f(x, c);
            y = f(f(y, c), c);
            d = __gcd(abs(x - y), n);
        }
        if (d != n) return d;
    }
}

// Recursive factorization
void factor_rec(int n, vector<int>& fac) {
    if (n == 1) return;
    if (is_prime(n)) {
        fac.push_back(n);
        return;
    }
    int d = pollard_rho(n);
    factor_rec(d, fac);
    factor_rec(n / d, fac);
}

// Wrapper: returns sorted prime factors
vector<int> factor(int n) {
    vector<int> fac;
    factor_rec(n, fac);
    sort(fac.begin(), fac.end());
    return fac;
}

// Demo
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cout << "Enter number: ";
    cin >> n;

    vector<int> f = factor(n);

    if (f.empty()) {
        cout << n << " has no prime factors.\n";
        return 0;
    }

    cout << n << " = ";
    for (size_t i = 0; i < f.size(); ++i) {
        if (i) cout << " * ";
        cout << f[i];
    }
    cout << "\n";

    return 0;
}
