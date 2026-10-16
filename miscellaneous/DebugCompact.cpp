#include <bits/stdc++.h>
using namespace std;
#define int long long
// C++17. Copy the struct and macro into your solution. Output goes to cerr.
struct Debug {
    template<class T>
    static void print(const T& x) {
        if constexpr (is_convertible_v<T, string_view>) cerr << '"' << x << '"';
        else if constexpr (is_same_v<T, bool>) cerr << (x ? "true" : "false");
        else if constexpr (is_same_v<T, char>) cerr << '\'' << x << '\'';
        else if constexpr (is_arithmetic_v<T>) cerr << x;
        else {
            cerr << '{';
            const char* sep = "";
            for (const auto& v : x) {
                cerr << sep; print(v); sep = ", ";
            }
            cerr << '}';
        }
    }
    template<class T>
    static void print(const vector<vector<T>>& grid) {
        cerr << '{';
        for (const auto& row : grid) {
            cerr << "\n  "; print(row);
        }
        if (!grid.empty()) cerr << '\n';
        cerr << '}';
    }
    template<class A, class B>
    static void print(const pair<A, B>& x) {
        cerr << '('; print(x.first);
        cerr << ", "; print(x.second); cerr << ')';
    }
    template<class... T>
    static void log(int line, const char* names, const T&... values) {
        cerr << line << ": [" << names << "] = ";
        const char* sep = "";
        ((cerr << sep, print(values), sep = " | "), ...);
        cerr << '\n';
    }
};
#define debug(...) Debug::log(__LINE__, #__VA_ARGS__, __VA_ARGS__)

signed main() {
    vector<int> a = {1, 2, 3};
    vector<vector<int>> grid = {{1, 2}, {3, 4}};
    map<string, vector<int>> groups = {{"even", {2, 4}}, {"odd", {1, 3}}};
    set<int> seen = {3, 1, 2};
    pair<int, string> entry = {7, "seven"};
    vector<bool> flags = {true, false};
    string name = "ICPC";
    int big = 1LL << 40;

    debug(a);
    debug(grid);
    debug(groups);
    debug(seen, entry);
    debug(flags, name);
    debug(42, true, 'A');
    debug(big);
}
