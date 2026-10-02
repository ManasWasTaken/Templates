#include <bits/stdc++.h>
using namespace std;

#define int long long

// ============================================================================
// SUFFIX ARRAY in O(n log n) + LCP (Kasai) + O(1) LCP of any two suffixes.
// Works for ANY characters (uses an internal sentinel smaller than every char,
// so strings with ' ', '!', '#', '$' ... are fine). 0-indexed.
// ----------------------------------------------------------------------------
// SuffixArray S(s);
// S.sa[i]                  start of the i-th smallest suffix          (size n)
// S.rk[i]                  position of suffix i inside sa (inverse)   (size n)
// S.lcp[i]                 LCP(suffix sa[i], suffix sa[i+1])           (size n-1)
// S.lcp_of(i, j)           LCP of suffixes s[i..] and s[j..]
//                          O(1), first call builds a sparse table in O(n log n)
// S.count(p)               number of occurrences of p in s            O(|p| log n)
//                          (occurrence starts = sa[lo..hi), see count())
// S.distinct_substrings()  n(n+1)/2 - sum(lcp)                         O(n)
//
// Common uses:
//   compare s[a..a+L) with s[b..b+L): equal iff lcp_of(a, b) >= L,
//       otherwise compare s[a + lcp] with s[b + lcp]
//   longest repeated substring = max(lcp)
//   longest common substring of a, b: build on a + sep + b (sep = char in neither),
//       answer = max lcp[i] where sa[i], sa[i+1] lie on different sides of sep
// ============================================================================
struct SuffixArray {
    int n;
    string s;
    vector<int> sa, rk, lcp;
    vector<vector<int>> sp; // sparse table over lcp, built on first lcp_of()

    SuffixArray(const string &str) : n(str.size()), s(str) {
        build_sa();
        build_lcp();
    }

    void build_sa() {
        int m = n + 1; // + sentinel with class 0
        vector<int> p(m), c(m), pn(m), cn(m), cnt(max<int>(m, 257), 0);
        for (int i = 0; i < n; i++) c[i] = (unsigned char)s[i] + 1;
        c[n] = 0;
        for (int i = 0; i < m; i++) cnt[c[i]]++;
        for (int i = 1; i < (int)cnt.size(); i++) cnt[i] += cnt[i - 1];
        for (int i = m - 1; i >= 0; i--) p[--cnt[c[i]]] = i;
        cn[p[0]] = 0;
        int classes = 1;
        for (int i = 1; i < m; i++) {
            if (c[p[i]] != c[p[i - 1]]) classes++;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
        for (int h = 1; h < m && classes < m; h <<= 1) {
            for (int i = 0; i < m; i++) {
                pn[i] = p[i] - h;
                if (pn[i] < 0) pn[i] += m;
            }
            fill(cnt.begin(), cnt.begin() + classes, 0);
            for (int i = 0; i < m; i++) cnt[c[pn[i]]]++;
            for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
            for (int i = m - 1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
            cn[p[0]] = 0;
            classes = 1;
            for (int i = 1; i < m; i++) {
                int a = p[i], b = p[i - 1];
                if (c[a] != c[b] || c[(a + h) % m] != c[(b + h) % m]) classes++;
                cn[a] = classes - 1;
            }
            c.swap(cn);
        }
        sa.assign(p.begin() + 1, p.end()); // p[0] is the sentinel
        rk.assign(n, 0);
        for (int i = 0; i < n; i++) rk[sa[i]] = i;
    }

    void build_lcp() {
        lcp.assign(max<int>(n - 1, 0), 0);
        for (int i = 0, k = 0; i < n; i++) {
            if (rk[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = sa[rk[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
            lcp[rk[i]] = k;
            if (k) k--;
        }
    }

    void build_sparse() {
        int m = lcp.size();
        sp.assign(1, lcp);
        for (int k = 1; (1 << k) <= m; k++) {
            sp.emplace_back(m - (1 << k) + 1);
            for (int i = 0; i + (1 << k) <= m; i++)
                sp[k][i] = min(sp[k - 1][i], sp[k - 1][i + (1 << (k - 1))]);
        }
    }

    int lcp_of(int i, int j) {
        if (i == j) return n - i;
        if (sp.empty()) build_sparse();
        int l = rk[i], r = rk[j];
        if (l > r) swap(l, r);
        int k = __lg(r - l); // min over lcp[l .. r-1]
        return min(sp[k][l], sp[k][r - (1 << k)]);
    }

    int count(const string &p) {
        auto lo = std::lower_bound(sa.begin(), sa.end(), p, [&](int i, const string &q) {
            return s.compare(i, q.size(), q) < 0;
        });
        auto hi = std::upper_bound(sa.begin(), sa.end(), p, [&](const string &q, int i) {
            return s.compare(i, q.size(), q) > 0;
        });
        return hi - lo;
    }

    long long distinct_substrings() {
        long long res = (long long)n * (n + 1) / 2;
        for (int x : lcp) res -= x;
        return res;
    }
};
