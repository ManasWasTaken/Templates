#include <bits/stdc++.h>
using namespace std;

#define int long long

// ============================================================================
// MINIMUM VERTEX COVER - smallest set of vertices that touches every edge.
// NP-hard in general, so use the version that fits the graph:
//   1. Bipartite graph            -> Konig: |min cover| = |max matching|   O(E sqrt(V))
//   2. Tree / forest              -> DP                                    O(n)
//   3. General graph, n < 64      -> branching on bitmasks                 O(1.38^n * n)
//   Weighted bipartite            -> min cut with Dinic (MaxFlow.C):
//        S -> u (cap w[u]) for u in L,  u -> v (cap INF) per edge,  v -> T (cap w[v]) for v in R
//        min cover weight = max flow; cover = (L NOT reachable from S) + (R reachable from S)
//        in the residual graph after the flow.
// Related facts:
//   max independent set = all vertices - min vertex cover
//   bipartite, no isolated vertices: min edge cover = n - max matching
//   DAG: min vertex-disjoint path cover = n - max matching (left = out-copy, right = in-copy)
//   max clique of G = max independent set of the complement of G
// ============================================================================

// ----------------------------------------------------------------------------
// 1. BIPARTITE: Hopcroft-Karp max matching + Konig min vertex cover.
// HopcroftKarp hk(nl, nr);    left vertices 0..nl-1, right vertices 0..nr-1
// hk.add_edge(u, v);          edge between left u and right v
// hk.max_matching();          size of a maximum matching (call before the cover)  O(E sqrt(V))
// hk.ml[u], hk.mr[v]          partner of left u / right v, -1 if unmatched
// hk.min_vertex_cover();      {left vertices, right vertices} of a minimum cover  O(V + E)
//                             max independent set = all vertices NOT in the cover
// ----------------------------------------------------------------------------
struct HopcroftKarp {
    int nl, nr;
    vector<vector<int>> adj;
    vector<int> ml, mr, dist;

    HopcroftKarp(int nl, int nr) : nl(nl), nr(nr), adj(nl), ml(nl, -1), mr(nr, -1), dist(nl) {}

    void add_edge(int u, int v) { adj[u].push_back(v); }

    bool bfs() {
        queue<int> q;
        bool found = false;
        for (int u = 0; u < nl; u++) {
            dist[u] = (ml[u] == -1) ? 0 : -1;
            if (ml[u] == -1) q.push(u);
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                int w = mr[v];
                if (w == -1) found = true;
                else if (dist[w] == -1) {
                    dist[w] = dist[u] + 1;
                    q.push(w);
                }
            }
        }
        return found;
    }

    bool dfs(int u) {
        for (int v : adj[u]) {
            int w = mr[v];
            if (w == -1 || (dist[w] == dist[u] + 1 && dfs(w))) {
                ml[u] = v;
                mr[v] = u;
                return true;
            }
        }
        dist[u] = -1; // dead end for this phase
        return false;
    }

    int max_matching() {
        int res = 0;
        while (bfs())
            for (int u = 0; u < nl; u++)
                if (ml[u] == -1 && dfs(u)) res++;
        return res;
    }

    pair<vector<int>, vector<int>> min_vertex_cover() {
        // Z = vertices reachable from free left vertices by alternating paths
        vector<bool> zl(nl, false), zr(nr, false);
        queue<int> q;
        for (int u = 0; u < nl; u++) {
            if (ml[u] == -1) {
                zl[u] = true;
                q.push(u);
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (zr[v]) continue;
                zr[v] = true;
                int w = mr[v];
                if (w != -1 && !zl[w]) {
                    zl[w] = true;
                    q.push(w);
                }
            }
        }
        vector<int> L, R; // cover = (L not in Z) + (R in Z)
        for (int u = 0; u < nl; u++) if (!zl[u]) L.push_back(u);
        for (int v = 0; v < nr; v++) if (zr[v]) R.push_back(v);
        return {L, R};
    }
};

// ----------------------------------------------------------------------------
// 2. TREE / FOREST: DP, iterative (no recursion depth issues).   O(n)
// tree_mvc(adj)   size of a minimum vertex cover of an undirected forest
// dp0[v] = best for v's subtree with v NOT taken -> every child must be taken
// dp1[v] = best for v's subtree with v taken     -> each child picks its better option
// Weighted version: start with dp1[v] = w[v] instead of 1.
// ----------------------------------------------------------------------------
int tree_mvc(const vector<vector<int>> &adj) {
    int n = adj.size(), res = 0;
    vector<int> par(n, -1), dp0(n, 0), dp1(n, 1), order;
    vector<bool> seen(n, false);
    for (int r = 0; r < n; r++) {
        if (seen[r]) continue;
        order = {r};
        seen[r] = true;
        for (int i = 0; i < (int)order.size(); i++) {
            for (int v : adj[order[i]]) {
                if (seen[v]) continue;
                seen[v] = true;
                par[v] = order[i];
                order.push_back(v);
            }
        }
        for (int i = (int)order.size() - 1; i > 0; i--) {
            int v = order[i], p = par[v];
            dp0[p] += dp1[v];
            dp1[p] += min(dp0[v], dp1[v]);
        }
        res += min(dp0[r], dp1[r]);
    }
    return res;
}

// ----------------------------------------------------------------------------
// 3. GENERAL GRAPH, small n (n < 64): exact search on bitmasks.
// g[v] = bitmask of the neighbours of v (no self loops). Returns the cover as a bitmask:
//     ull cover = mvc_small(g, (1ULL << n) - 1);     size = __builtin_popcountll(cover)
// Rules: a vertex with exactly 1 neighbour -> take that neighbour (always optimal);
//        otherwise take a max-degree v and branch: v in cover / all neighbours of v in cover.
// Worst case T(n) = T(n-1) + T(n-4) -> O(1.38^n * n); in practice much faster
// (random 3..6-regular graphs with n = 62 take a few milliseconds).
// ----------------------------------------------------------------------------
using ull = unsigned long long;
ull mvc_small(const vector<ull> &g, ull alive) {
    int v = -1, best = 0;
    for (ull m = alive; m; m &= m - 1) {
        int u = __builtin_ctzll(m), d = __builtin_popcountll(g[u] & alive);
        if (d == 1) {
            ull x = g[u] & alive;
            return x | mvc_small(g, alive & ~x & ~(1ULL << u));
        }
        if (d > best) best = d, v = u;
    }
    if (v == -1) return 0; // no edges left
    ull nb = g[v] & alive;
    ull a = (1ULL << v) | mvc_small(g, alive & ~(1ULL << v));
    ull b = nb | mvc_small(g, alive & ~nb & ~(1ULL << v));
    return __builtin_popcountll(a) <= __builtin_popcountll(b) ? a : b;
}
