#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Fenwick2D {
    int n, m;
    vector<vector<int>> bit;

    Fenwick2D(int n, int m) : n(n), m(m) {
        bit.assign(n, vector<int>(m, 0));
    }

    void add(int x, int y, int val) {
        for (int i = x; i < n; i = i | (i + 1))
            for (int j = y; j < m; j = j | (j + 1))
                bit[i][j] += val;
    }

    // sum of rectangle (0,0) -> (x,y)
    // 0-based (inclusive)
    int pref(int x, int y) {
        if (x < 0 || y < 0) return 0;
        int s = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
                s += bit[i][j];
        return s;
    }

    // sum of rectangle (x1,y1) -> (x2,y2)
    int range(int x1, int y1, int x2, int y2) {
        return pref(x2, y2)
             - pref(x1 - 1, y2)
             - pref(x2, y1 - 1)
             + pref(x1 - 1, y1 - 1);
    }
};