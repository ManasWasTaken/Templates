#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Prefix2D {
    int n, m;
    vector<vector<int>> pref;

    Prefix2D(vector<vector<int>> &a) {
        n = a.size();
        m = a[0].size();
        pref.assign(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                pref[i][j] = a[i - 1][j - 1]
                           + pref[i - 1][j]
                           + pref[i][j - 1]
                           - pref[i - 1][j - 1];
            }
        }
    }

    // returns sum of submatrix
    // from (x1,y1) to (x2,y2) inclusive (0-based)
    int query(int x1, int y1, int x2, int y2) {
        x1++; y1++; x2++; y2++;
        return pref[x2][y2]
             - pref[x1 - 1][y2]
             - pref[x2][y1 - 1]
             + pref[x1 - 1][y1 - 1];
    }
};