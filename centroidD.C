// JAI SHREE RAM //
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) 8
#endif
const int M=1e9+7;
const int INF=1e18;
#define int long long
struct bin_lift{
    vector<vector<int>> adj,p;
    vector<int> depth;
    int root,n;
    int log=20;
    bin_lift(){}
    bin_lift(int root,int n,const vector<vector<int>> &adj):root(root), n(n), adj(adj){
        
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
struct CentroidDecomposition{
    int n;
    vector<int> subtree;
    vector<int> p;
    vector<int> tree;
    vector<int> visited;
    bin_lift lca;
    vector<vector<int>> adj;
    CentroidDecomposition(const vector<vector<int>> &adj) : adj(adj) , n(adj.size()) ,lca(0,adj.size(),adj){
        subtree.assign(n,0);
        p.assign(n,0);
        tree.assign(n,INF);
        visited.assign(n,0);
        build(0,-1);
    }

    void SubtreeDfs(int node,int parent){
        subtree[node]=1;
        for(auto x:adj[node]){
            if(x==parent || visited[x]==1) continue;
            SubtreeDfs(x,node);
            subtree[node]+=subtree[x];
        }
    }

    int getCentroid(int node,int parent,int N){
        for(auto x:adj[node]){
            if(visited[x]==1 || x==parent) continue;
            if(subtree[x]>N/2){
                return getCentroid(x,node,N);
            }
        }
        return node;
    }

    void build(int node,int parent){
        SubtreeDfs(node,-1);
        int c=getCentroid(node,-1,subtree[node]);
        p[c]=parent;
        visited[c]=1;
        for(auto x:adj[c]){
            if(visited[x]==1) continue;
            build(x,c);
        }
    }
    
    void update(int node){
        int x=node;
        while(node!=-1){
            tree[node]=min(tree[node],lca.get_distance(x,node));
            node=p[node];
        }
    }

    int query(int node){
        int x=node;
        int res=INF;
        while(node!=-1){
            res=min(res,tree[node] + lca.get_distance(x,node));
            node=p[node];
        }
        return res;
    }

};
void solve(){
    int n,q;
    cin>>n>>q;
    vector<vector<int>> adj(n);
    for(int i=1;i<n;i++){
        int a,b;
        cin>>a>>b;
        a--,b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    CentroidDecomposition decomp(adj);
    decomp.update(0);
    while(q--){
        int a,node;
        cin>>a>>node;
        node--;
        if(a==1){
            decomp.update(node);
        }
        else{
            cout<<decomp.query(node)<<"\n";
        }
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