#include <bits/stdc++.h>
using namespace std;

#define int long long

// ============================================================================
// AHO-CORASICK - match many patterns in one pass over a text.
// Build O(total pattern length * K), each text char O(1).
// ----------------------------------------------------------------------------
// AhoCorasick ac;
// int id = ac.add(p);          add every pattern first (ids 0, 1, 2, ...)
// ac.build();                  then build ONCE
// ac.count_each(text)          vector<long long> c, c[id] = occurrences of pattern id
//                              in text (overlapping, duplicates handled)   O(|text| + nodes)
// ac.total_matches(text)       total number of (end position, pattern) matches
// ac.go(v, ch)                 automaton transition from state v by char ch
// ac.cnt[v]                    number of patterns that are suffixes of state v's string
//
// DP over the automaton (e.g. "count strings of length L containing no pattern"):
//   states 0..ac.size()-1, start at 0, move with go(v, ch), state v is forbidden iff cnt[v] > 0
// Alphabet: K letters starting at BASE ('a'..'z'). Change both for other alphabets.
// ============================================================================
struct AhoCorasick {
    static const int K = 26;
    static const char BASE = 'a';
    vector<array<int32_t, K>> nxt; // int32_t: stays 4 bytes even with #define int long long
    vector<int32_t> link;          // suffix link
    vector<int> cnt;               // patterns ending here, incl. via suffix links (after build)
    vector<int> term;              // term[id] = node where pattern id ends
    vector<int> order;             // BFS order of non-root nodes

    AhoCorasick() { new_node(); }

    int new_node() {
        nxt.emplace_back();
        nxt.back().fill(-1);
        link.push_back(0);
        cnt.push_back(0);
        return (int)nxt.size() - 1;
    }

    int size() { return nxt.size(); }

    int add(const string &p) {
        int v = 0;
        for (char ch : p) {
            int c = ch - BASE;
            if (nxt[v][c] == -1) {
                int u = new_node();
                nxt[v][c] = u;
            }
            v = nxt[v][c];
        }
        cnt[v]++;
        term.push_back(v);
        return (int)term.size() - 1;
    }

    void build() {
        queue<int> q;
        for (int c = 0; c < K; c++) {
            if (nxt[0][c] == -1) nxt[0][c] = 0;
            else q.push(nxt[0][c]);
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            order.push_back(v);
            cnt[v] += cnt[link[v]];
            for (int c = 0; c < K; c++) {
                int u = nxt[v][c];
                if (u == -1) {
                    nxt[v][c] = nxt[link[v]][c];
                } else {
                    link[u] = nxt[link[v]][c];
                    q.push(u);
                }
            }
        }
    }

    int go(int v, char ch) { return nxt[v][ch - BASE]; }

    vector<long long> count_each(const string &text) {
        vector<long long> hit(nxt.size(), 0);
        int v = 0;
        for (char ch : text) {
            v = nxt[v][ch - BASE];
            hit[v]++;
        }
        for (int i = (int)order.size() - 1; i >= 0; i--) hit[link[order[i]]] += hit[order[i]];
        vector<long long> res(term.size());
        for (int i = 0; i < (int)term.size(); i++) res[i] = hit[term[i]];
        return res;
    }

    long long total_matches(const string &text) {
        long long res = 0;
        int v = 0;
        for (char ch : text) {
            v = nxt[v][ch - BASE];
            res += cnt[v];
        }
        return res;
    }
};
