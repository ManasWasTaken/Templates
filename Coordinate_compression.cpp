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
struct CC{
    vector<int> arr;
    int n_;
    CC(vector<int> &a):arr(a){
        sort(arr.begin(),arr.end());
        arr.erase(unique(arr.begin(),arr.end()),arr.end());
        n_=arr.size();
    }
    int get_val(int idx){
        assert(idx<n_);
        return arr[idx];
    }
    int get_index(int val){
        auto temp=lower_bound(arr.begin(),arr.end(),val);
        return temp-arr.begin();
    }
};
void solve(){
    
}
int32_t main(){
    cout<<fixed;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<setprecision(15)<<fixed;
    int t=1;
    while(t--){
       solve(); 
    }
    return 0;
}