#include <bits/stdc++.h>
using namespace std;

#define int long long

// ============================================================================
// DIGIT DP SKELETON - count numbers in [L, R] whose digits satisfy some property.
// Bounds are decimal strings, so R can be up to 10^1000 (use long long overloads below
// for normal inputs).
// ----------------------------------------------------------------------------
// count_upto(X)        how many x in [0, X] are good
// count_range(L, R)    how many x in [L, R] are good  (= count_upto(R) - count_upto(L - 1))
//
// Recursion state:
//   pos     current digit index (0 = most significant)
//   st      YOUR state: previous digit, digit sum, number % k, count of some digit, ...
//   tight   digits so far equal X's prefix -> next digit can go only up to X[pos]
//   started a non-zero digit has been placed (false = still in leading zeros, number is 0 so far)
// Only states with tight == false are memoized (the tight path is unique per pos).
// Complexity: O(len * STATES * 2 * 10).
//
// Change the 3 places marked "CHANGE". Example filled in: no two adjacent digits are equal
// (CSES "Counting Numbers"). Other common choices:
//   digit sum == S   : STATES = S + 1, nst = st + d (skip if > S),  end: return st == S
//   divisible by k   : STATES = k,     nst = (st * 10 + d) % k,     end: return st == 0
//   count of digit 7 : STATES = len+1, nst = st + (d == 7),         end: return st == wanted
// Answer modulo M: take % M where res is added.
// Need sum of numbers instead of count: return pair {count, sum} and add d * 10^(n-1-pos) * count.
// Many queries with the same property: index memo by (n - pos) instead of pos and keep it
// global, so it is reused across calls (valid because the non-tight state ignores X).
// ============================================================================
long long count_upto(const string &X) {
    int n = X.size();
    const int STATES = 10; // CHANGE: number of possible values of st
    vector<vector<array<long long, 2>>> memo(n, vector<array<long long, 2>>(STATES, {-1, -1}));

    auto rec = [&](auto &&self, int pos, int st, bool tight, bool started) -> long long {
        if (pos == n) {
            return 1; // CHANGE: 1 if the finished number is good (started == false means x = 0)
        }
        if (!tight && memo[pos][st][started] != -1) return memo[pos][st][started];
        long long res = 0;
        int lim = tight ? X[pos] - '0' : 9;
        for (int d = 0; d <= lim; d++) {
            bool nstarted = started || d != 0;
            // CHANGE: skip bad digits with continue, compute the next state nst
            if (started && d == st) continue;
            int nst = d;
            res += self(self, pos + 1, nst, tight && d == lim, nstarted);
        }
        if (!tight) memo[pos][st][started] = res;
        return res;
    };
    return rec(rec, 0, 0, true, false);
}

string minus_one(string s) { // s >= 1, no leading zeros
    int i = (int)s.size() - 1;
    while (s[i] == '0') s[i--] = '9';
    s[i]--;
    if (s.size() > 1 && s[0] == '0') s.erase(0, 1);
    return s;
}

long long count_range(const string &L, const string &R) {
    long long res = count_upto(R);
    if (L != "0") res -= count_upto(minus_one(L));
    return res;
}

long long count_upto(long long X) { return X < 0 ? 0 : count_upto(to_string(X)); }
long long count_range(long long L, long long R) { return count_upto(R) - count_upto(L - 1); }
