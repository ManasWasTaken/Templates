// JAI SHREE RAM //
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) 8
#endif
const int M=1e9+7;
#define int long long

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
static uniform_int_distribution<int> dist(1, 1000000000); // Inclusive.
int rnd() {
    return dist(rng);
}

void solve(){
    
}
int32_t main(){
    cout<<fixed;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<setprecision(15)<<fixed;

    cout << rnd() << '\n';

    vector<int> a = {1, 2, 3, 4, 5};
    shuffle(a.begin(), a.end(), rng);
    for (int x : a) cout << x << ' ';
    cout << '\n';

    int b[] = {10, 20, 30, 40};
    shuffle(begin(b), end(b), rng);
    for (int x : b) cout << x << ' ';
    cout << '\n';

    int t=1;
    while(t--){
       solve();
    }
    return 0;
}
