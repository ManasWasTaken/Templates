#include <bits/stdc++.h>
using namespace std;

#define int long long

int kosaraju(int n, vector<vector<int>> &adj) {
    
    vector<int> vis(n, 0);
    stack<int> st;

    auto dfs1 = [&](int u, auto &&self) ->void {
        vis[u] = 1;
        for (int v : adj[u]) {
            if (!vis[v]) self(v, self);
        }
        st.push(u);
    };

    for (int i = 0; i < n; i++) {
        if (!vis[i]) dfs1(i, dfs1);
    }

    vector<vector<int>> radj(n);
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            radj[v].push_back(u);
        }
    }

    fill(vis.begin(), vis.end(), 0);

    auto dfs2 = [&](int u, auto &&self) -> void {
        vis[u] = 1;
        for (int v : radj[u]) {
            if (!vis[v]) self(v, self);
        }
    };

    int scc = 0;

    while (!st.empty()) {
        int u = st.top();
        st.pop();
        if (!vis[u]) {
            scc++;
            dfs2(u, dfs2);
        }
    }

    return scc;
}