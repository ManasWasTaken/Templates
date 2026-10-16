#include <bits/stdc++.h>
using namespace std;

#define int long long

// ============================================================================
// ITERATING OVER SUBMASKS / SUPERMASKS
// ----------------------------------------------------------------------------
// All submasks s of mask, from mask down to 0:                  O(2^popcount(mask))
//     for (int s = mask; ; s = (s - 1) & mask) {
//         ... use s ...
//         if (s == 0) break;
//     }
// Only non-empty submasks:          for (int s = mask; s > 0; s = (s - 1) & mask)
// Non-empty proper submasks (s != mask, s != 0):
//                                   for (int s = (mask - 1) & mask; s > 0; s = (s - 1) & mask)
// All supermasks of mask in n bits:                             O(2^(n - popcount(mask)))
//     for (int s = mask; s < (1 << n); s = (s + 1) | mask)
// Every mask together with all its submasks (see min_partition):  O(3^n) total
//     n = 13 -> 1.6e6, n = 16 -> 4.3e7, n = 18 -> 3.9e8, n = 20 -> 3.5e9 (too slow, use SOS)
// ============================================================================

// Example: split all n items into groups at minimum total cost, cost[s] = cost of group s.
// Only submasks containing the lowest bit of mask are tried, so each split is counted once.
// O(3^n)
long long min_partition(const vector<long long> &cost, int n) {
    vector<long long> dp(1 << n, LLONG_MAX / 2);
    dp[0] = 0;
    for (int mask = 1; mask < (1 << n); mask++) {
        int low = mask & -mask;
        for (int s = mask; s > 0; s = (s - 1) & mask)
            if (s & low) dp[mask] = min(dp[mask], dp[mask ^ s] + cost[s]);
    }
    return dp[(1 << n) - 1];
}

// ============================================================================
// SOS DP (sum over subsets / supersets) on B bits, f.size() == 1 << B.   O(B * 2^B)
// ----------------------------------------------------------------------------
// sos_subset(f, B):    f[mask] = sum of original f[s] over all SUBMASKS s of mask
// sos_superset(f, B):  f[mask] = sum of original f[s] over all SUPERMASKS s of mask
// Undo a transform (Mobius inversion): same loops with -= instead of +=
// For max / min instead of sum: replace += with max / min.
// B = 20 -> 2e7 operations.
// ============================================================================
void sos_subset(vector<long long> &f, int B) {
    for (int i = 0; i < B; i++)
        for (int mask = 0; mask < (1 << B); mask++)
            if (mask >> i & 1) f[mask] += f[mask ^ (1 << i)];
}

void sos_superset(vector<long long> &f, int B) {
    for (int i = 0; i < B; i++)
        for (int mask = 0; mask < (1 << B); mask++)
            if (!(mask >> i & 1)) f[mask] += f[mask | (1 << i)];
}

// Example (inclusion-exclusion over supersets): number of non-empty subsets of a
// (all a[i] < 2^B) whose bitwise AND is 0, modulo MOD.
// cnt[mask] = how many a[i] are supermasks of mask -> 2^cnt - 1 subsets have AND ⊇ mask
// answer = sum over mask of (-1)^popcount(mask) * (2^cnt[mask] - 1).     O(B * 2^B + n)
long long and_zero_subsets(const vector<int> &a, int B, long long MOD = 1000000007) {
    vector<long long> cnt(1 << B, 0), pw(a.size() + 1, 1);
    for (int x : a) cnt[x]++;
    sos_superset(cnt, B);
    for (int i = 1; i <= (int)a.size(); i++) pw[i] = pw[i - 1] * 2 % MOD;
    long long ans = 0;
    for (int mask = 0; mask < (1 << B); mask++) {
        long long t = (pw[cnt[mask]] - 1 + MOD) % MOD;
        ans = (__builtin_popcountll(mask) & 1) ? (ans - t + MOD) % MOD : (ans + t) % MOD;
    }
    return ans;
}

// random integer in [l, r] inclusive
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
