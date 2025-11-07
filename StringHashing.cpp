// to convert a string into a hash in O(n)
// single rolling hash
const int MOD = 1000000007;
const int BASE = 131;      
vector<int> h, pw;
void build_hash(const string &s) {
    int n = s.size();
    h.assign(n + 1, 0);
    pw.assign(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        h[i] = (h[i - 1] * BASE + s[i - 1]) % MOD;
        pw[i] = (pw[i - 1] * BASE) % MOD;
    }
}
int get_hash(int l, int r) {  // 0-indexed substring [l, r]
    int res = (h[r + 1] - h[l] * pw[r - l + 1]) % MOD;
    if (res < 0) res += MOD;
    return res;
}

// double rolling hash for extra collision security
// access via creating object then calling these methods
struct DoubleHash {
    const int mod1 = 1000000007;
    const int mod2 = 1000000009;
    const int base = 131;
    vector<int> h1, h2, p1, p2;
    void build(const string &s) {
        int n = s.size();
        h1.assign(n + 1, 0); h2.assign(n + 1, 0);
        p1.assign(n + 1, 1); p2.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            h1[i] = (h1[i - 1] * base + s[i - 1]) % mod1;
            h2[i] = (h2[i - 1] * base + s[i - 1]) % mod2;
            p1[i] = (p1[i - 1] * base) % mod1;
            p2[i] = (p2[i - 1] * base) % mod2;
        }
    }
    pair<int, int> get(int l, int r) {  // substring [l, r], 0-indexed
        int x1 = (h1[r + 1] - h1[l] * p1[r - l + 1]) % mod1;
        int x2 = (h2[r + 1] - h2[l] * p2[r - l + 1]) % mod2;
        if (x1 < 0) x1 += mod1;
        if (x2 < 0) x2 += mod2;
        return {x1, x2};
    }
};