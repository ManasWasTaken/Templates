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
struct bin_lift{
    vector<vector<int>> adj,p;
    vector<int> depth;
    int root,n;
    int log=20;
    bin_lift(int root,int n,vector<vector<int>> adj):root(root), n(n), adj(adj){
        p.assign(n,vector<int> (log,0));
        depth.assign(n,0);
        for(int i=0;i<log;i++){
            p[root][i]=root;
        }
        dfs(root,-1);
    }
    void dfs(int node,int Parent){
        for(auto x:adj[node]){
            if(x==Parent) continue;
            depth[x]=depth[node]+1;
            p[x][0]=node;
            for(int i=1;i<log;i++){
                p[x][i]=p[p[x][i-1]][i-1];
            }
            dfs(x,node);
        }
        return;
    }
 
    int get_parent(int node,int k){
        if(k>depth[node]) return -1;
        for(int i=log-1;i>=0;i--){
            if(k&(1<<i)){
                node=p[node][i];
            }
        }
        return node;
    }

    int get_lca(int a,int b){
        if(depth[b]>depth[a]){
            swap(a,b);
        }
        int diff=depth[a]-depth[b];
        for(int i=log-1;i>=0;i--){
            if((1<<i)&diff){
                a=p[a][i];
            }
        }
        if(a==b) return a;
        for(int i=log-1;i>=0;i--){
            if(p[a][i]!=p[b][i]){
                a=p[a][i];
                b=p[b][i];
            }
        }
        return p[a][0];
    }

    int get_distance(int a,int b){
        int parent=get_lca(a,b);
        int distance=depth[a]+depth[b]-(2*depth[parent]);
        return distance;
    }
};
//can be improved in terms of time complexity
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