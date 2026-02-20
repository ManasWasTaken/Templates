#include <bits/stdc++.h>
using namespace std;

#define int long long

struct DSU {
    vector<int> p, sz;
    vector<pair<int*, int>> history;

    DSU(int n) {
        p.resize(n);
        sz.assign(n, 1);
        iota(p.begin(), p.end(), 0);
    }

    int find(int x) {
        while (x != p[x])
            x = p[x];
        return x;
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;

        if (sz[a] < sz[b]) swap(a, b);

        history.push_back({&p[b], p[b]});
        history.push_back({&sz[a], sz[a]});

        p[b] = a;
        sz[a] += sz[b];

        return true;
    }

    int snapshot() {
        return history.size();
    }

    void rollback(int snap) {
        while ((int)history.size() > snap) {
            *history.back().first = history.back().second;
            history.pop_back();
        }
    }
};