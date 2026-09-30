#include <bits/stdc++.h>
using namespace std;
// C++17. Copy the struct and macro into your solution. Output goes to cerr.
struct Debug {
    template<class T>
    static void print(const T& x) {
        if constexpr (std::is_convertible_v<T, std::string_view>) {
            std::cerr << '"' << x << '"';
        } else if constexpr (std::is_same_v<T, bool>) {
            std::cerr << (x ? "true" : "false");
        } else if constexpr (std::is_same_v<T, char>) {
            std::cerr << '\'' << x << '\'';
        } else if constexpr (std::is_arithmetic_v<T>) {
            std::cerr << x;
        } else {
            std::cerr << '{';
            const char* sep = "";
            for (const auto& v : x) {
                std::cerr << sep; print(v); sep = ", ";
            }
            std::cerr << '}';
        }
    }
    template<class T>
    static void print(const std::vector<std::vector<T>>& grid) {
        std::cerr << '{';
        for (const auto& row : grid) {
            std::cerr << "\n  "; print(row);
        }
        if (!grid.empty()) std::cerr << '\n';
        std::cerr << '}';
    }
    template<class A, class B>
    static void print(const std::pair<A, B>& x) {
        std::cerr << '('; print(x.first);
        std::cerr << ", "; print(x.second); std::cerr << ')';
    }
    template<class... T>
    static void log(int line, const char* names, const T&... values) {
        std::cerr << line << ": [" << names << "] = ";
        const char* sep = "";
        ((std::cerr << sep, print(values), sep = " | "), ...);
        std::cerr << '\n';
    }
};
#define debug(...) Debug::log(__LINE__, #__VA_ARGS__, __VA_ARGS__)

int main() {
    vector<int> a = {1, 2, 3};
    vector<vector<int>> grid = {{1, 2}, {3, 4}};
    map<string, vector<int>> groups = {{"even", {2, 4}}, {"odd", {1, 3}}};
    set<int> seen = {3, 1, 2};
    pair<int, string> entry = {7, "seven"};
    vector<bool> flags = {true, false};
    string name = "ICPC";

    debug(a);
    debug(grid);
    debug(groups);
    debug(seen, entry);
    debug(flags, name);
    debug(42, true, 'A');
}
