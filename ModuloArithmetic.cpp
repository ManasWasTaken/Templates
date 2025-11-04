// JAI SHREE RAM //
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) 8
#endif
const int M=1e9+7;

const int MAXN = 1e6; // adjust if needed

long long fact[MAXN + 1];
long long invFact[MAXN + 1];
long long power[MAXN + 1];
long long invPower[MAXN + 1];

long long mod_pow(long long a, long long b) {
    long long res = 1;
    a %= M;
    while (b > 0) {
        if (b & 1) res = (res * a) % M;
        a = (a * a) % M;
        b >>= 1;
    }
    return res;
}

long long mod_inv(long long a) {
    return mod_pow(a, M - 2);
}

void precompute_factorials() {
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        fact[i] = (fact[i - 1] * i) % M;

    invFact[MAXN] = mod_inv(fact[MAXN]);
    for (int i = MAXN - 1; i >= 0; i--)
        invFact[i] = (invFact[i + 1] * (i + 1)) % M;
}

void precompute_powers(long long base) {
    power[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        power[i] = (power[i - 1] * base) % M;

    long long invBase = mod_inv(base);
    invPower[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        invPower[i] = (invPower[i - 1] * invBase) % M;
}

long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[r] % M * invFact[n - r] % M;
}

long long nPr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[n - r] % M;
}

void solve(){
    
}
int32_t main(){
    cout<<fixed;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<setprecision(15)<<fixed;
    int t=1;
    while(t--){
       solve(); 
    }
    return 0;
}