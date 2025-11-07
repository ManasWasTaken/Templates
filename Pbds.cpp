// JAI SHREE RAM //
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) 8
#endif

// -------------------- CONSTANTS --------------------
const int M = 1e9 + 7;
#define int long long

// -------------------- ORDERED SET TEMPLATE --------------------
// Ordered Set: supports order_of_key() and find_by_order()
// order_of_key(k) → # of elements strictly less than k
// find_by_order(k) → iterator to k-th element (0-indexed)
template <class T>
using ordered_set = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

void solve(){
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(15) << fixed;

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
