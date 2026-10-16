#include <bits/stdc++.h>
using namespace std;

#define int long long

// ============================================================================
// PALINDROMIC TREE (EERTREE) - one node per DISTINCT palindromic substring.
// O(n) nodes, O(n) amortized time, memory O(n * K).
// Node 0 = imaginary root (len -1), node 1 = empty string (len 0). Real nodes are 2, 3, ...
// ----------------------------------------------------------------------------
// PalindromicTree pt(s);       builds and already calls build_occ()
//   (online: PalindromicTree pt; pt.add(c) per char; pt.build_occ() ONCE at the end)
// pt.distinct()                number of distinct non-empty palindromic substrings
// pt.len[v]                    length of the palindrome at node v
// pt.link[v]                   node of the longest proper palindromic suffix of v
// pt.firstend[v]               end index of its first occurrence
//                              -> palindrome = s.substr(firstend[v] - len[v] + 1, len[v])
// pt.occ[v]                    number of occurrences of palindrome v in s (after build_occ)
// pt.last                      node of the longest palindromic suffix of the current string
// pt.depth[pt.last]            number of palindromic substrings ENDING at the current
//                              position (sum over positions = all palindromic substrings)
// Alphabet: K letters starting at BASE.
// ============================================================================
struct PalindromicTree {
    static const int K = 26;
    static const char BASE = 'a';
    vector<array<int32_t, K>> nxt; // int32_t: stays 4 bytes even with #define int long long
    vector<int32_t> len, link, depth, firstend;
    vector<long long> occ;
    string s;
    int last = 1;

    PalindromicTree() {
        new_node(-1, 0); // node 0
        new_node(0, 0);  // node 1
    }

    PalindromicTree(const string &str) : PalindromicTree() {
        for (char ch : str) add(ch);
        build_occ();
    }

    int new_node(int l, int lk) {
        nxt.emplace_back();
        nxt.back().fill(-1);
        len.push_back(l);
        link.push_back(lk);
        depth.push_back(0);
        firstend.push_back(-1);
        occ.push_back(0);
        return (int)len.size() - 1;
    }

    int get_link(int v, int i) { // longest suffix palindrome of v that extends with s[i]
        while (i - len[v] - 1 < 0 || s[i - len[v] - 1] != s[i]) v = link[v];
        return v;
    }

    void add(char ch) {
        s += ch;
        int i = (int)s.size() - 1, c = ch - BASE;
        int v = get_link(last, i);
        if (nxt[v][c] == -1) {
            int u = new_node(len[v] + 2, 0);
            link[u] = (len[u] == 1) ? 1 : nxt[get_link(link[v], i)][c];
            depth[u] = depth[link[u]] + 1;
            firstend[u] = i;
            nxt[v][c] = u;
        }
        last = nxt[v][c];
        occ[last]++;
    }

    void build_occ() {
        for (int v = (int)len.size() - 1; v >= 2; v--) occ[link[v]] += occ[v];
    }

    int distinct() { return (int)len.size() - 2; }
};
