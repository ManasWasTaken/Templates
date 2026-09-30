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
using pii=pair<int,int>;
struct CartTree { 
    vector<int> l,r; //left children could be -1 and right can be n
    vector<array<int,2>> adj; //0-> left, 1->right
    int root;
    CartTree(const vector<pii>& a) : l(a.size()),r(a.size()),adj(a.size(),{-1,-1}) { // max at the root, then has two chilidren, if equal maxes, take rightmost one as the root.
        int n = a.size();
        for(int i=0;i<n;++i) {
            l[i]=i-1;
            while(l[i]>=0 and a[l[i]]<=a[i]) { //prev greater
                l[i]=l[l[i]];
            }
        }
        for(int i=n-1;i>=0;--i) {
            r[i]=i+1;
            while(r[i]<n and a[r[i]]<a[i]) { //next greater
                r[i]=r[r[i]];
            }
        }
 
        for(int i=0;i<n;++i) {
            if(l[i]==-1 and r[i]==n) { //largest becomes root
                root=i;
            } else if(l[i]==-1) { 
                adj[r[i]][0]=i; 
            } else if(r[i]==n) { 
                adj[l[i]][1]=i; 
            } else if(a[l[i]]<=a[r[i]]) {
                adj[l[i]][1]=i;
            } else adj[r[i]][0]=i;
        }
    }
};
void solve(){
    //code here
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