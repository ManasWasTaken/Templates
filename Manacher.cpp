#include <bits/stdc++.h>
using namespace std;

#define int long long

// ============================================================================
// MANACHER - palindrome radius at EVERY centre in O(n). 0-indexed.
// ----------------------------------------------------------------------------
// Manacher m(s);
// m.d1[i]          number of ODD palindromes centred at i
//                  longest = s[i - d1[i] + 1 .. i + d1[i] - 1], length 2*d1[i] - 1
// m.d2[i]          number of EVEN palindromes centred between i-1 and i
//                  longest = s[i - d2[i] .. i + d2[i] - 1],     length 2*d2[i]
// m.is_pal(l, r)   is s[l..r] a palindrome? (inclusive)                 O(1)
// m.count_all()    number of palindromic substrings, counted by position
//                  (= sum d1 + sum d2)                                  O(n)
// m.longest()      {start, length} of a longest palindromic substring   O(n)
// ============================================================================
struct Manacher {
    int n;
    vector<int> d1, d2;

    Manacher(const string &s) : n(s.size()), d1(n), d2(n) {
        for (int i = 0, l = 0, r = -1; i < n; i++) {
            int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
            while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
            d1[i] = k--;
            if (i + k > r) l = i - k, r = i + k;
        }
        for (int i = 0, l = 0, r = -1; i < n; i++) {
            int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
            while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;
            d2[i] = k--;
            if (i + k > r) l = i - k - 1, r = i + k;
        }
    }

    bool is_pal(int l, int r) {
        int len = r - l + 1;
        if (len <= 0) return true;
        if (len & 1) return d1[(l + r) / 2] >= (len + 1) / 2;
        return d2[(l + r + 1) / 2] >= len / 2;
    }

    long long count_all() {
        long long c = 0;
        for (int i = 0; i < n; i++) c += d1[i] + d2[i];
        return c;
    }

    pair<int, int> longest() {
        int st = 0, len = (n > 0);
        for (int i = 0; i < n; i++) {
            if (2 * d1[i] - 1 > len) len = 2 * d1[i] - 1, st = i - d1[i] + 1;
            if (2 * d2[i] > len) len = 2 * d2[i], st = i - d2[i];
        }
        return {st, len};
    }
};
