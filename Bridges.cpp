#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<vector<int>> bridges;
vector<int> tin, low, vis;
int timer;

void dfs(int u, int p, vector<vector<int>> &adj) {
    vis[u] = 1;
    tin[u] = low[u] = timer++;

    for (int v : adj[u]) {
        if (v == p) continue;

        if (!vis[v]) {
            dfs(v, u, adj);
            low[u] = min(low[u], low[v]);

            if (low[v] > tin[u])
                bridges.push_back({u, v});
        } else {
            low[u] = min(low[u], tin[v]);
        }
    }
}

vector<vector<int>> find_bridges(int n, vector<vector<int>> &adj) {
    bridges.clear();
    tin.assign(n, 0);
    low.assign(n, 0);
    vis.assign(n, 0);
    timer = 0;

    for (int i = 0; i < n; i++)
        if (!vis[i])
            dfs(i, -1, adj);

    return bridges;
}