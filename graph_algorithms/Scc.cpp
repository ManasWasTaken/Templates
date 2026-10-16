#include <bits/stdc++.h>
using namespace std;

#define int long long

// ============================================================================
// SCC (Kosaraju) + condensation DAG. 0-indexed directed graph.  O(n + m)
// ----------------------------------------------------------------------------
// SCC s(adj);              adj[u] = out-neighbours of u
// s.cnt                    number of strongly connected components
// s.comp[v]                component id of v. Ids are in TOPOLOGICAL order:
//                          for every edge u -> v, comp[u] <= comp[v]
//                          (process DAG DP in order 0..cnt-1, or reverse for "reachable" DP)
// s.dag[c]                 condensation edges c -> d (c < d), no duplicates, no self loops
// s.members[c]             vertices of component c (size = members[c].size())
// 2-SAT (node 2i = x_i, 2i+1 = !x_i): unsat iff comp[2i] == comp[2i+1],
//                          else x_i = comp[2i] > comp[2i+1]
// Recursive DFS: depth can reach n, fine on judges with a large stack.
// ============================================================================
struct SCC {
    int n, cnt = 0;
    vector<int> comp, order;
    vector<vector<int>> radj, dag, members;

    SCC(const vector<vector<int>> &adj) : n(adj.size()), comp(n, -1), radj(n) {
        vector<bool> vis(n, false);
        auto dfs1 = [&](int u, auto &&self) -> void {
            vis[u] = true;
            for (int v : adj[u]) if (!vis[v]) self(v, self);
            order.push_back(u);
        };
        auto dfs2 = [&](int u, auto &&self) -> void {
            comp[u] = cnt;
            for (int v : radj[u]) if (comp[v] == -1) self(v, self);
        };
        for (int u = 0; u < n; u++) {
            if (!vis[u]) dfs1(u, dfs1);
            for (int v : adj[u]) radj[v].push_back(u);
        }
        for (int i = n - 1; i >= 0; i--) {
            if (comp[order[i]] == -1) {
                dfs2(order[i], dfs2);
                cnt++;
            }
        }
        dag.resize(cnt);
        members.resize(cnt);
        for (int u = 0; u < n; u++) {
            members[comp[u]].push_back(u);
            for (int v : adj[u])
                if (comp[u] != comp[v]) dag[comp[u]].push_back(comp[v]);
        }
        for (auto &e : dag) {
            sort(e.begin(), e.end());
            e.erase(unique(e.begin(), e.end()), e.end());
        }
    }
};
