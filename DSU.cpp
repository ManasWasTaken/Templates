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
struct DSU{
    vector<int> parent;
    vector<int> size;
    int n;
    DSU(int x) : n(x) , size(x+1,1), parent(x+1,0){
        iota(parent.begin(),parent.end(),0);
    }
 
    int get(int node){
        if(parent[node]==node) return node;
        return parent[node]=get(parent[node]);
    }
    
    void unite(int a,int b){
        a=get(a);
        b=get(b);
        if(a==b) return;
        if(size[a]<size[b]){
            swap(a,b);
        }
        parent[b]=a;
        size[a]+=size[b];
        return;
    }
    
    int getSize(int node){
        node=get(node);
        return size[node];
    }
};
//can be improved
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