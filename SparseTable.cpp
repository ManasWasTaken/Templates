// JAI SHREE RAM //
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) 8
#endif
#define int long long
const int M=1e9+7;
const int N=2e5+10;
int sp[21][N];
int mn[N];
int arr[N];
int n,q;
void precompute(){
    //best to use for max,min and gcd
    for(int i=1;i<=n;i++){
        sp[0][i]=arr[i];
    }
    for(int i=1;(1ll<<i)<=n;i++){
        for(int j=1;j +(1ll<<i) -1<=n;j++){
            sp[i][j]=min(sp[i-1][j],sp[i-1][j+(1ll<<(i-1))]);
        }
    }
    mn[1]=0;
    for(int i=2;i<=n;i++){
        mn[i]=mn[i/2] + 1;
    }
}
int query(int l,int r){
    int i=mn[r-l+1];
    return min(sp[i][l],sp[i][r-(1ll<<i)+1]);
}
void solve(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    precompute();
    while(q--){
        int l,r;
        cin>>l>>r;
        cout<<query(l,r)<<"\n";
    }
    return;
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