#include <bits/stdc++.h>
using namespace std;

#define int long long
#define nl '\n'

vector<int> tin, low, vis, isAP;
int timer;

void dfs(int u, int p, vector<vector<int>> &adj) {
    vis[u] = 1;
    tin[u] = low[u] = timer++;
    int child = 0;

    for (int v : adj[u]) {
        if (v == p) continue;

        if (!vis[v]) {
            dfs(v, u, adj);
            low[u] = min(low[u], low[v]);

            if (low[v] >= tin[u] && p != -1)
                isAP[u] = 1;

            child++;
        } else {
            low[u] = min(low[u], tin[v]);
        }
    }

    if (p == -1 && child > 1)
        isAP[u] = 1;
}

vector<int> articulation_points(int n, vector<vector<int>> &adj) {
    tin.assign(n, 0);
    low.assign(n, 0);
    vis.assign(n, 0);
    isAP.assign(n, 0);
    timer = 0;

    for (int i = 0; i < n; i++)
        if (!vis[i])
            dfs(i, -1, adj);

    vector<int> res;
    for (int i = 0; i < n; i++)
        if (isAP[i])
            res.push_back(i);

    if (res.empty()) return {-1};
    return res;
}