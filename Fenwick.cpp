#include <bits/stdc++.h>
using namespace std;

#define int long long

// ============================================================================
// FENWICK TREE (BIT) - point add, prefix sum, range sum. 0-indexed. O(log n) each.
// T = value type: long long for normal sums, Z (mint) for sums modulo M.
// ----------------------------------------------------------------------------
// Fenwick<long long> f(n);    n zeros   (fill: for each i, f.add(i, a[i]))
// f.add(i, v);                a[i] += v
// f.pref(i);                  a[0] + ... + a[i]    (0 if i < 0)
// f.range(l, r);              a[l] + ... + a[r]    inclusive
// Range add + point query:    f.add(l, v); f.add(r + 1, -v);   a[i] = f.pref(i)
//                             (with Z write Z(0) - v instead of -v)
// ============================================================================
template <class T>
struct Fenwick {
    int n;
    vector<T> t; // t[1..n], 1-indexed internally

    Fenwick(int n) : n(n), t(n + 1) {}

    void add(int i, T v) {
        for (i++; i <= n; i += i & -i) t[i] += v;
    }

    T pref(int i) {
        T s{};
        for (i++; i > 0; i -= i & -i) s += t[i];
        return s;
    }

    T range(int l, int r) {
        if (l > r) return T{};
        return pref(r) - pref(l - 1);
    }
};
