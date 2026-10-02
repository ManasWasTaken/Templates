#include <bits/stdc++.h>
using namespace std;

#define int long long

// ============================================================================
// SUFFIX AUTOMATON - every substring of s is a path from state 0.
// <= 2n states, build O(n * K). A state = all substrings with the same set of
// end positions; len[v] = longest of them, link[v] = suffix link.
// ----------------------------------------------------------------------------
// SuffixAutomaton sam(s);      builds and already calls build_occ()
//   (online: SuffixAutomaton sam; sam.extend(c) per char; sam.build_occ() ONCE at the end)
// sam.contains(p)              is p a substring of s                        O(|p|)
// sam.occurrences(p)           number of occurrences of p in s              O(|p|)
// sam.first_occurrence(p)      start index of first occurrence, -1 if none  O(|p|)
// sam.distinct_substrings()    number of distinct non-empty substrings      O(n)
// sam.lcs(t)                   {length, start in t} of the longest common
//                              substring of s and t                         O(|t|)
// sam.kth(k)                   k-th (1-indexed) lexicographically smallest DISTINCT
//                              substring, "" if k is too large    O(n K) once, then O(|ans| K)
// sam.occ[v]                   |endpos(v)| = occurrences of every string in state v
//
// Alphabet: K letters starting at BASE. Memory ~ 2n * K * 4 bytes
// (n = 5e5, K = 26 -> ~104 MB). If too much, switch nxt to map<char, int>.
// ============================================================================
struct SuffixAutomaton {
    static const int K = 26;
    static const char BASE = 'a';
    vector<array<int32_t, K>> nxt; // int32_t: stays 4 bytes even with #define int long long
    vector<int32_t> len, link, firstpos;
    vector<long long> occ, ways;
    int last = 0;

    SuffixAutomaton() { new_state(0, -1, -1); }

    SuffixAutomaton(const string &s) : SuffixAutomaton() {
        nxt.reserve(2 * s.size() + 1);
        for (char ch : s) extend(ch);
        build_occ();
    }

    int new_state(int l, int lk, int fp) {
        nxt.emplace_back();
        nxt.back().fill(-1);
        len.push_back(l);
        link.push_back(lk);
        firstpos.push_back(fp);
        occ.push_back(0);
        return (int)len.size() - 1;
    }

    void extend(char ch) {
        int c = ch - BASE;
        int cur = new_state(len[last] + 1, 0, len[last]);
        occ[cur] = 1;
        int p = last;
        while (p != -1 && nxt[p][c] == -1) {
            nxt[p][c] = cur;
            p = link[p];
        }
        if (p != -1) {
            int q = nxt[p][c];
            if (len[p] + 1 == len[q]) {
                link[cur] = q;
            } else {
                int cl = new_state(len[p] + 1, link[q], firstpos[q]);
                nxt[cl] = nxt[q];
                while (p != -1 && nxt[p][c] == q) {
                    nxt[p][c] = cl;
                    p = link[p];
                }
                link[q] = link[cur] = cl;
            }
        }
        last = cur;
    }

    vector<int> by_len() { // states sorted by len (counting sort)
        int sz = len.size(), mx = 0;
        for (int v = 0; v < sz; v++) mx = max(mx, (int)len[v]);
        vector<int> c(mx + 1, 0), order(sz);
        for (int v = 0; v < sz; v++) c[len[v]]++;
        for (int i = 1; i <= mx; i++) c[i] += c[i - 1];
        for (int v = sz - 1; v >= 0; v--) order[--c[len[v]]] = v;
        return order;
    }

    void build_occ() {
        vector<int> order = by_len();
        for (int i = (int)order.size() - 1; i > 0; i--) occ[link[order[i]]] += occ[order[i]];
    }

    int walk(const string &p) { // state after reading p, -1 if p is not a substring
        int v = 0;
        for (char ch : p) {
            v = nxt[v][ch - BASE];
            if (v == -1) return -1;
        }
        return v;
    }

    bool contains(const string &p) { return walk(p) != -1; }

    long long occurrences(const string &p) {
        int v = walk(p);
        return v == -1 ? 0 : occ[v];
    }

    int first_occurrence(const string &p) {
        int v = walk(p);
        return v == -1 ? -1 : firstpos[v] - (int)p.size() + 1;
    }

    long long distinct_substrings() {
        long long r = 0;
        for (int v = 1; v < (int)len.size(); v++) r += len[v] - len[link[v]];
        return r;
    }

    pair<int, int> lcs(const string &t) {
        int v = 0, l = 0, best = 0, end = 0;
        for (int i = 0; i < (int)t.size(); i++) {
            int c = t[i] - BASE;
            while (v && nxt[v][c] == -1) {
                v = link[v];
                l = len[v];
            }
            if (nxt[v][c] != -1) {
                v = nxt[v][c];
                l++;
            }
            if (l > best) best = l, end = i;
        }
        return {best, best ? end - best + 1 : 0};
    }

    string kth(long long k) {
        if (ways.empty()) { // ways[v] = 1 (stop here) + strings continuing from v
            ways.assign(len.size(), 1);
            vector<int> order = by_len();
            for (int i = (int)order.size() - 1; i >= 0; i--) {
                int v = order[i];
                for (int c = 0; c < K; c++)
                    if (nxt[v][c] != -1) ways[v] += ways[nxt[v][c]];
            }
        }
        if (k < 1 || k > ways[0] - 1) return "";
        string res;
        int v = 0;
        while (k > 0) {
            for (int c = 0; c < K; c++) {
                int u = nxt[v][c];
                if (u == -1) continue;
                if (k <= ways[u]) {
                    res += char(BASE + c);
                    k--;
                    v = u;
                    break;
                }
                k -= ways[u];
            }
        }
        return res;
    }
};
